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
	void RenderDevice::AddRenderer(Renderer* renderer)
	{
		int position = FindFirstIndexInBatch(renderer);
		m_renderers.insert(m_renderers.begin() + position, renderer);
		m_isIndexArrayDirty = true;
	}

	void RenderDevice::UpdateRenderer(Renderer* renderer)
	{
		m_renderers.erase(std::remove(m_renderers.begin(), m_renderers.end(), renderer), m_renderers.end());
		AddRenderer(renderer);
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

		// render batched
		std::vector<BatchRange> batches = ComputeBatches();
		for (unsigned int i = 0; i < batches.size(); i++)
		{
			unsigned int batchBegin = batches[i].min;
			unsigned int batchSize = batches[i].Diff() + 1;
			Renderer* prototype = m_renderers[batchBegin];

			// init batch prototype
			if (prototype->GetMaterial()->GetTexture() != NULL)
				prototype->GetMaterial()->GetTexture()->Bind();
			prototype->GetMaterial()->GetShader()->Use();
			prototype->GetMaterial()->PrepareShaderVariables();

			// set position shader variable
			unsigned int vaoStartIndex = ComputeVaoStartIndex(i, batches);
			int positionAttribLocation = prototype->GetMaterial()->GetShader()->GetAttributeLocation("a_vPosition");
			glEnableVertexAttribArray(positionAttribLocation);
			glVertexAttribPointer(positionAttribLocation, 2, GL_FLOAT, GL_FALSE, prototype->GetMesh()->GetVertexSize() * sizeof(GLfloat), &(m_vertexArray[vaoStartIndex]));

			// set texture coordinate shader variable
			if (prototype->GetMaterial()->GetTexture() != NULL)
			{
				int texCoordAttribLocation = prototype->GetMaterial()->GetShader()->GetAttributeLocation("a_vTexCoord");
				glEnableVertexAttribArray(texCoordAttribLocation);
				glVertexAttribPointer(texCoordAttribLocation, 2, GL_FLOAT, GL_FALSE, prototype->GetMesh()->GetVertexSize() * sizeof(GLfloat), &(m_vertexArray[vaoStartIndex + 2]));
			}

			// draw batched
			// unsigned int numIndices = prototype->GetMesh()->GetIndices()->size();
			unsigned int numIndices = GetNumIndices(prototype);
			glDrawElements(GL_TRIANGLES, batchSize * numIndices, GL_UNSIGNED_INT, &m_indexArray[batchBegin * numIndices]);

			// cleanup
			prototype->GetMaterial()->GetShader()->Unuse();
			if (prototype->GetMaterial()->GetTexture() != NULL)
				glDisableVertexAttribArray(prototype->GetMaterial()->GetShader()->GetAttributeLocation("a_vTexCoord"));
			glDisableVertexAttribArray(positionAttribLocation);

		#ifdef ORBIS_DEBUG_RENDERDEVICE
					count++;
		#endif 
				}

		#ifdef ORBIS_DEBUG_RENDERDEVICE
				LogHelper::LogMessage("%d", count);
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
	
	unsigned int RenderDevice::GetNumIndices(Renderer* renderer)
	{
		return renderer->GetMesh()->GetIndices()->size();
	}

	unsigned int RenderDevice::GetNumIndices(ParticleRenderer* renderer)
	{
		return renderer->GetMesh()->GetIndices()->size() * renderer->GetRenderTransforms().size();
	}


	void RenderDevice::UpdateVertexArray()
	{
		Matrix3 worldCamMatrix = Camera::GetInstance()->CalcCamMatrix(TransformSpace::WorldSpace);
		Matrix3 localCamMatrix = Camera::GetInstance()->CalcCamMatrix(TransformSpace::CameraSpace);

		m_vertexArray.clear();
		ReserveVertexArray();

		for (unsigned int i = 0; i < m_renderers.size(); i++)
		{
			std::vector<Transform> transforms = m_renderers[i]->GetRenderTransforms();
			for (unsigned int j = 0; j < transforms.size(); j++)
			{
				Entity* entity = m_renderers[i]->GetParent();
				bool isWorldSpace = entity->GetTransform()->transformSpace == TransformSpace::WorldSpace ? true : false;
				Matrix3 mvpMatrix = (isWorldSpace ? worldCamMatrix : localCamMatrix) * transforms[j].GetModelMatrix();
				InsertIntoVertexArray(m_renderers[i], mvpMatrix);
			}
		}
	}

	void RenderDevice::InsertIntoVertexArray(Renderer* const renderer, Matrix3& mvpMatrix)
	{
		Mesh* mesh = renderer->GetMesh();
		Texture* tex = renderer->GetMaterial()->GetTexture();

		// apply transformation on mesh data
		std::vector<GLfloat> data = *mesh->GetVertexData();
		for (unsigned int j = 0; j < mesh->GetNumVertices(); j++)
		{
			unsigned int start = j * mesh->GetVertexSize();
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
		for (unsigned int i = 0; i < m_renderers.size(); i++)
		{
			vertexArraySize += m_renderers[i]->GetMesh()->GetNumVertices() * m_renderers[i]->GetRenderTransforms().size();
		}

		m_vertexArray.reserve(vertexArraySize);
	}

	void RenderDevice::UpdateIndexArray()
	{
		if (m_isIndexArrayDirty)
		{
			m_indexArray.clear();
			ReserveIndexArray();

			GLuint offset = 0;
			for (unsigned int i = 0; i < m_renderers.size(); i++)
			{
				InsertIntoIndexArray(i, offset);
			}

			m_isIndexArrayDirty = false;
		}
	}

	void RenderDevice::InsertIntoIndexArray(unsigned int index, unsigned int& offset)
	{
		// reset value offet when switching batch
		if (index == 0 || !m_renderers[index]->GetMaterial()->IsBatchEqualTo(m_renderers[index - 1]->GetMaterial()))
			offset = 0;

		for (unsigned int i = 0; i < m_renderers[index]->GetRenderTransforms().size(); i++)
		{
			Mesh* mesh = m_renderers[index]->GetMesh();
			for (unsigned int j = 0; j < mesh->GetIndices()->size(); j++)
			{
				GLuint value = offset + mesh->GetIndices()->at(j);
				m_indexArray.insert(m_indexArray.end(), value);
			}

			offset += mesh->GetNumVertices();
		}
	}

	void RenderDevice::ReserveIndexArray()
	{
		unsigned int size = 0;
		for (unsigned int i = 0; i < m_renderers.size(); i++)
			size += m_renderers[i]->GetMesh()->GetIndices()->size();

		m_indexArray.reserve(size);
	}

	unsigned int RenderDevice::ComputeVaoStartIndex(unsigned int batchIndex, std::vector<BatchRange> batches)
	{
		unsigned int startIndex = 0;

		for (unsigned int i = 0; i < batchIndex; i++)
		{
			unsigned int begin = batches[i].min;
			unsigned int batchSize = batches[i].Diff() + 1;
			startIndex += m_renderers[begin]->GetMesh()->GetVertexData()->size() * batchSize;
		}

		return startIndex;
	}

	std::vector<BatchRange> RenderDevice::ComputeBatches()
	{
		std::vector<BatchRange> batches;
		int begin = 0;
		int current = 0;
		int last = m_renderers.size();

		while (current < last)
		{
			while (current < last && m_renderers[begin]->GetMaterial()->IsBatchEqualTo(m_renderers[current]->GetMaterial()))
				current++;

			batches.push_back(BatchRange(begin, current - 1));
			begin = current;

			if (current == last)
				break;
		}

		return batches;
	}

	int RenderDevice::FindFirstIndexInBatch(Renderer* renderer)
	{
		for (unsigned int i = 0; i < m_renderers.size(); i++)
		{
			if (renderer->GetMaterial()->IsBatchEqualTo(m_renderers[i]->GetMaterial()))
				return i;
		}

		return m_renderers.size();
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

