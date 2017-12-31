#include "RenderDevice.h"

#include "Mesh.h"
#include "Shader.h"
#include "VideoManager.h"

#include "../Components/Camera.h"
using namespace Components;

#include <algorithm>

// #define ORBIS_DEBUG_RENDER_DEVICE

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
		// set states
		glActiveTexture(GL_TEXTURE0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// update arrays
		UpdateIndexArray();
		UpdateVertexArray();

		// render batched
		#ifdef ORBIS_DEBUG_RENDER_DEVICE
			int count = 0;
		#endif // ORBIS_DEBUG_RENDER_DEVICE 
		unsigned int vaoStartIndex = 0;
		unsigned int lastBatchBegin = 0;
		for (unsigned int batchBegin = 0; batchBegin < m_renderers.size(); batchBegin++)
		{
			// compute batch indices
			unsigned int batchEnd = batchBegin;
			for (unsigned int j = batchBegin; j < m_renderers.size(); j++)
			{
				if (!m_renderers[batchBegin]->GetMaterial()->IsBatchEqualTo(m_renderers[j]->GetMaterial()))
					break;
				batchEnd = j;
			}

			// accumulate the current vertex start index
			for (unsigned int i = lastBatchBegin; i < batchBegin; i++)
				vaoStartIndex += m_renderers[i]->GetMesh()->GetVertexData()->size();

			// set batch texture
			Renderer* prototype = m_renderers[batchBegin];
			if (prototype->GetMaterial()->GetTexture() != NULL)
				prototype->GetMaterial()->GetTexture()->Bind();

			// set batch shader
			prototype->GetMaterial()->GetShader()->Use();
			prototype->GetMaterial()->PrepareShaderVariables();

			// set batch position shader variable
			int positionAttribLocation = prototype->GetMaterial()->GetShader()->GetAttributeLocation("a_vPosition");
			glEnableVertexAttribArray(positionAttribLocation);
			glVertexAttribPointer(positionAttribLocation, 2, GL_FLOAT, GL_FALSE, prototype->GetMesh()->GetVertexSize() * sizeof(GLfloat), &(m_vertexArray[vaoStartIndex]));

			// set batch texture coordinate shader variable
			if (prototype->GetMaterial()->GetTexture() != NULL)
			{
				int texCoordAttribLocation = prototype->GetMaterial()->GetShader()->GetAttributeLocation("a_vTexCoord");
				glEnableVertexAttribArray(texCoordAttribLocation);
				glVertexAttribPointer(texCoordAttribLocation, 2, GL_FLOAT, GL_FALSE, prototype->GetMesh()->GetVertexSize() * sizeof(GLfloat), &(m_vertexArray[vaoStartIndex + 2]));
			}

			// draw batched
			unsigned int numIndices = prototype->GetMesh()->GetIndices()->size();
			glDrawElements(GL_TRIANGLES, (batchEnd - batchBegin + 1) * numIndices, GL_UNSIGNED_INT, &m_indexArray[batchBegin * numIndices]);

			// cleanup batch
			prototype->GetMaterial()->GetShader()->Unuse();
			if (prototype->GetMaterial()->GetTexture() != NULL)
				glDisableVertexAttribArray(prototype->GetMaterial()->GetShader()->GetAttributeLocation("a_vTexCoord"));
			glDisableVertexAttribArray(positionAttribLocation);

			lastBatchBegin = batchBegin;
			batchBegin = batchEnd;

			#ifdef ORBIS_DEBUG_RENDER_DEVICE
				count++;
			#endif // ORBIS_DEBUG_RENDER_DEVICE
		}

		#ifdef ORBIS_DEBUG_RENDER_DEVICE
			std::cout << count << std::endl;
		#endif // ORBIS_DEBUG_RENDER_DEVICE

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

		unsigned int current = 0;
		for (unsigned int i = 0; i < m_renderers.size(); i++)
		{
			Mesh* mesh = m_renderers[i]->GetMesh();
			Texture* tex = m_renderers[i]->GetMaterial()->GetTexture();
			const std::vector<GLfloat>* mvd = mesh->GetVertexData();
			Entity* entity = m_renderers[i]->GetParent();
			bool isWorldSpace = entity->GetTransform()->transformSpace == TransformSpace::WorldSpace ? true : false;
			Matrix3 mvpMatrix = (isWorldSpace ? worldCamMatrix : localCamMatrix) * entity->GetTransform()->GetModelMatrix();

			m_vertexArray.insert(m_vertexArray.end(), mvd->begin(), mvd->end());

			// apply transformation in vertex array
			for (unsigned int j = 0; j < mesh->GetNumVertices(); j++)
			{
				Vector2D pos = mvpMatrix * Vector2D(m_vertexArray[current], m_vertexArray[current + 1]);
				m_vertexArray[current] = pos.x;
				m_vertexArray[current + 1] = pos.y;
				if (tex) {
					Vector2D uvCoord = Vector2D(m_vertexArray[current + 2], m_vertexArray[current + 3]);
					uvCoord = tex->MapUVCoord(uvCoord);
					m_vertexArray[current + 2] = uvCoord.x;
					m_vertexArray[current + 3] = uvCoord.y;
				}
				current += mesh->GetVertexSize();
			}
		}
	}

	void RenderDevice::ReserveVertexArray()
	{
		unsigned int vertexArraySize = 0;
		for (unsigned int i = 0; i < m_renderers.size(); i++)
		{
			vertexArraySize += m_renderers[i]->GetMesh()->GetNumVertices();
		}

		m_vertexArray.reserve(vertexArraySize);
	}

	void RenderDevice::UpdateIndexArray()
	{
		if (m_isIndexArrayDirty)
		{
			m_indexArray.clear();
			ReserveIndexArray();

			unsigned int totalNumIndices = 0;
			GLuint valueOffset = 0;
			for (unsigned int i = 0; i < m_renderers.size(); i++)
			{
				// reset value offet when switching batch
				if (i == 0 || !m_renderers[i]->GetMaterial()->IsBatchEqualTo(m_renderers[i - 1]->GetMaterial()))
					valueOffset = 0;

				Mesh* mesh = m_renderers[i]->GetMesh();
				for (unsigned int j = 0; j < mesh->GetIndices()->size(); j++)
				{
					GLuint value = valueOffset + mesh->GetIndices()->at(j);
					m_indexArray.insert(m_indexArray.begin() + totalNumIndices, value);
					totalNumIndices++;
				}

				valueOffset += mesh->GetNumVertices();
			}

			m_isIndexArrayDirty = false;
		}
	}

	void RenderDevice::ReserveIndexArray()
	{
		unsigned int size = 0;
		for (unsigned int i = 0; i < m_renderers.size(); i++)
			size += m_renderers[i]->GetMesh()->GetIndices()->size();

		m_indexArray.reserve(size);
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

