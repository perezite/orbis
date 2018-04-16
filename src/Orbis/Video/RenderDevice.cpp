#include "RenderDevice.h"

#include "Mesh.h"
#include "Shader.h"
#include "VideoManager.h"

#include "../Components/Camera.h"
#include "../Core/LogHelper.h"
#include "../Settings/Settings.h"
using namespace Components;
using namespace Core;

#include <algorithm>

namespace Video
{
	void RenderDevice::AddRenderable(Renderable* renderable)
	{
		int position = FindFirstIndexInBatch(renderable);
		m_renderables.insert(m_renderables.begin() + position, renderable);
		m_isIndexArrayDirty = true;
	}

	void RenderDevice::UpdateRenderable(Renderable* renderable)
	{
		DeleteRenderable(renderable);
		AddRenderable(renderable);
	}

	void RenderDevice::DeleteRenderable(Renderable* renderable)
	{
		m_renderables.erase(std::remove(m_renderables.begin(), m_renderables.end(), renderable), m_renderables.end());
	}

	void RenderDevice::Render()
	{ 
		#ifdef ORBIS_DEBUG_RENDERDEVICE
			int count = 0;
		#endif 

		// set states
		glActiveTexture(GL_TEXTURE0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// update arrays
		UpdateIndexArray();
		UpdateVertexArray();

		// skip if nothing to render
		if (m_vertexArray.size() == 0)
			return;

		// render batched
		std::vector<BatchRange> batches = ComputeBatches();
		for (unsigned int i = 0; i < batches.size(); i++)
		{
			unsigned int batchBegin = batches[i].min;
			unsigned int batchSize = batches[i].Diff() + 1;
			unsigned int vaoStartIndex = ComputeVaoStartIndex(i, batches);
			unsigned int iboStartIndex = ComputeIboStartIndex(i, batches);
			Renderable* prototype = m_renderables[batchBegin];

			// init batch prototype
			if (prototype->GetMaterial()->GetTexture() != NULL)
				prototype->GetMaterial()->GetTexture()->Bind();
			prototype->GetMaterial()->GetShader()->Use();
			prototype->GetMaterial()->PrepareShaderVariables();

			// set position shader variable
			unsigned int stride = prototype->GetMesh()->GetVertexData()->size();
			int positionAttribLocation = prototype->GetMaterial()->GetShader()->GetAttributeLocation("a_vPosition");
			glEnableVertexAttribArray(positionAttribLocation);
			glVertexAttribPointer(positionAttribLocation, 2, GL_FLOAT, GL_FALSE, stride, &(m_vertexArray[vaoStartIndex]));

			// set texture coordinate shader variable
			if (prototype->GetMaterial()->GetTexture() != NULL) {
				int texCoordAttribLocation = prototype->GetMaterial()->GetShader()->GetAttributeLocation("a_vTexCoord");
				glEnableVertexAttribArray(texCoordAttribLocation);
				glVertexAttribPointer(texCoordAttribLocation, 2, GL_FLOAT, GL_FALSE, stride, &(m_vertexArray[vaoStartIndex + 2]));
			}

			// set vertex color shader variable
			if (prototype->GetMesh()->IsVertexColored()) {
				int vertexColorAttribLocation = prototype->GetMaterial()->GetShader()->GetAttributeLocation("a_vVertexColor");
				glEnableVertexAttribArray(vertexColorAttribLocation);
				glVertexAttribPointer(vertexColorAttribLocation, 4, GL_FLOAT, GL_FALSE, stride, &(m_vertexArray[vaoStartIndex + 4]));
			}

			// draw batched
			glDrawElements(GL_TRIANGLES, batchSize * prototype->GetMesh()->GetIndices()->size(), GL_UNSIGNED_SHORT, &m_indexArray[iboStartIndex]);

			// cleanup
			prototype->GetMaterial()->GetShader()->Unuse();
			if (prototype->GetMaterial()->GetTexture() != NULL)
				glDisableVertexAttribArray(prototype->GetMaterial()->GetShader()->GetAttributeLocation("a_vTexCoord"));
			if (prototype->GetMesh()->IsVertexColored())
				glDisableVertexAttribArray(prototype->GetMaterial()->GetShader()->GetAttributeLocation("a_vVertexColor"));
			glDisableVertexAttribArray(positionAttribLocation);

		#ifdef ORBIS_DEBUG_RENDERDEVICE
					count++;
		#endif 
				}

		#ifdef ORBIS_DEBUG_RENDERDEVICE
				LogHelper::LogMessage("Number of draw calls: %d", count);
		#endif 

		// cleanup
		glDisable(GL_BLEND);
	}

	void RenderDevice::DrawDebugLine(Vector2D start, Vector2D end, Color color)
	{
		// compute vertex array
		Matrix3 camMatrix = Camera::GetInstance()->CalcCamMatrix();
		start = camMatrix * start;
		end = camMatrix * end;
		GLfloat vertexArray[4] = { start.x, start.y, end.x, end.y };

		glLineWidth(3);
		DrawDebugPrimitive(vertexArray, 4, color, RenderMode::Lines);
	}

	void RenderDevice::DrawDebugRect(Rect rect, Color color)
	{
		// compute vertex array
		Matrix3 camMatrix = Camera::GetInstance()->CalcCamMatrix();
		rect = camMatrix * rect;
		GLfloat vertexArray[12] = {
			rect.leftBottom.x , rect.leftBottom.y, rect.GetRightBottom().x, rect.GetRightBottom().y, rect.GetLeftTop().x, rect.GetLeftTop().y,
			rect.GetRightBottom().x, rect.GetRightBottom().y, rect.rightTop.x, rect.rightTop.y, rect.GetLeftTop().x, rect.GetLeftTop().y
		};

		DrawDebugPrimitive(vertexArray, 12, color, RenderMode::Triangles);
	}
	
	void RenderDevice::UpdateVertexArray()
	{
		Matrix3 worldCamMatrix = Camera::GetInstance()->CalcCamMatrix(TransformSpace::WorldSpace);
		Matrix3 localCamMatrix = Camera::GetInstance()->CalcCamMatrix(TransformSpace::CameraSpace);

		m_vertexArray.clear();
		ReserveVertexArray();

		for (unsigned int i = 0; i < m_renderables.size(); i++)
		{
			Transform* transform = m_renderables[i]->GetTransform();
			bool isWorldSpace = transform->transformSpace == TransformSpace::WorldSpace ? true : false;
			Matrix3 mvpMatrix = (isWorldSpace ? worldCamMatrix : localCamMatrix) * transform->GetModelMatrix();
			InsertIntoVertexArray(m_renderables[i], mvpMatrix);
		}
	}

	void RenderDevice::InsertIntoVertexArray(Renderable* const renderable, Matrix3& mvpMatrix)
	{
		Mesh* mesh = renderable->GetMesh();
		Texture* tex = renderable->GetMaterial()->GetTexture();

		// apply transformation on mesh data
		std::vector<GLfloat> data = *mesh->GetVertexData();
		for (unsigned int i = 0; i < mesh->GetNumVertices(); i++)
		{
			unsigned int start = i * mesh->GetVertexSize();
			Vector2D pos = mvpMatrix * Vector2D(data[start + 0], data[start + 1]);
			data[start + 0] = pos.x; data[start + 1] = pos.y;
			if (tex) {
				Vector2D uvCoord = tex->MapUVCoord(Vector2D(data[start + 2], data[start + 3]));
				data[start + 2] = uvCoord.x; data[start + 3] = uvCoord.y;
			}
		}

		m_vertexArray.insert(m_vertexArray.end(), data.begin(), data.end());
	}

	void RenderDevice::ReserveVertexArray()
	{
		unsigned int vertexArraySize = 0;
		for (unsigned int i = 0; i < m_renderables.size(); i++) {
			vertexArraySize += m_renderables[i]->GetMesh()->GetVertexData()->size();
		}

		m_vertexArray.reserve(vertexArraySize);
	}

	void RenderDevice::UpdateIndexArray()
	{
		if (m_isIndexArrayDirty)
		{
			m_indexArray.clear();
			ReserveIndexArray();

			GLushort offset = 0;
			for (unsigned int i = 0; i < m_renderables.size(); i++)
			{
				InsertIntoIndexArray(i, offset);
			}

			m_isIndexArrayDirty = false;
		}
	}

	void RenderDevice::InsertIntoIndexArray(unsigned int index, unsigned short& offset)
	{
		// reset value offet when switching batch
		if (index == 0 || !m_renderables[index]->IsBatchEqualTo(m_renderables[index - 1]))
			offset = 0;

		Mesh* mesh = m_renderables[index]->GetMesh();
		for (unsigned int j = 0; j < mesh->GetIndices()->size(); j++)
		{
			GLushort value = offset + mesh->GetIndices()->at(j);
			m_indexArray.insert(m_indexArray.end(), value);
		}

		offset += mesh->GetNumVertices();
	}

	void RenderDevice::ReserveIndexArray()
	{
		unsigned int size = 0;
		for (unsigned int i = 0; i < m_renderables.size(); i++)
			size += m_renderables[i]->GetMesh()->GetIndices()->size();

		m_indexArray.reserve(size);
	}

	unsigned int RenderDevice::ComputeVaoStartIndex(unsigned int batchIndex, std::vector<BatchRange> batches)
	{
		unsigned int startIndex = 0;

		for (unsigned int i = 0; i < batchIndex; i++)
		{
			unsigned int begin = batches[i].min;
			unsigned int batchSize = batches[i].Diff() + 1;
			startIndex += m_renderables[begin]->GetMesh()->GetVertexData()->size() * batchSize;
		}

		return startIndex;
	}

	unsigned int RenderDevice::ComputeIboStartIndex(unsigned int batchIndex, std::vector<BatchRange> batches)
	{
		unsigned int startIndex = 0;

		for (unsigned int i = 0; i < batchIndex; i++)
		{
			unsigned int begin = batches[i].min;
			unsigned int batchSize = batches[i].Diff() + 1;
			startIndex += m_renderables[begin]->GetMesh()->GetIndices()->size() * batchSize;
		}

		return startIndex;
	}

	std::vector<BatchRange> RenderDevice::ComputeBatches()
	{
		std::vector<BatchRange> batches;
		int begin = 0;
		int current = 0;
		int last = m_renderables.size();

		while (current < last)
		{
			while (current < last && m_renderables[begin]->IsBatchEqualTo(m_renderables[current]))
				current++;

			batches.push_back(BatchRange(begin, current - 1));
			begin = current;

			if (current == last)
				break;
		}

		return batches;
	}

	int RenderDevice::FindFirstIndexInBatch(Renderable* renderable)
	{
		for (unsigned int i = 0; i < m_renderables.size(); i++)
		{
			if (renderable->IsBatchEqualTo(m_renderables[i]))
				return i;
		}

		return m_renderables.size();
	}

	void RenderDevice::DrawDebugPrimitive(GLfloat * vertexArray, unsigned int vertexArraySize, Color color, RenderMode renderMode)
	{
		// prepare
		glDisable(GL_BLEND);
		Shader* shader = Shader::GetFlatShader();
		shader->Use();
		shader->SetUniform("u_vColor", color);
		int positionAttribLocation = shader->GetAttributeLocation("a_vPosition");
		glEnableVertexAttribArray(positionAttribLocation);
		glVertexAttribPointer(positionAttribLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), vertexArray);

		// draw
		glDrawArrays(renderMode, 0, vertexArraySize / 2);

		// cleanup
		glDisableVertexAttribArray(positionAttribLocation);
		shader->Unuse();
	}
}

