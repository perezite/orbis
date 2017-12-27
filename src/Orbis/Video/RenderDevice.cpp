#include "RenderDevice.h"

#include "Mesh_v2.h"
#include "Shader.h"
#include "VideoManager.h"

#include "../Components/Camera.h"
using namespace Components;

namespace Video
{
	void RenderDevice::AddRenderer(Renderer* renderer)
	{
		int position = FindFirstIndexInBatch(renderer);
		m_renderers.insert(m_renderers.begin() + position, renderer);
		m_isIndexArrayDirty = true;
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
		unsigned int vaoStartIndex = 0;
		unsigned int lastBatchBegin = 0;
		for (unsigned int batchBegin = 0; batchBegin < m_renderers.size(); batchBegin++)
		{
			// compute batch indices
			unsigned int batchEnd = batchBegin;
			for (unsigned int j = batchBegin; j < m_renderers.size(); j++)
			{
				if (!m_renderers[batchBegin]->IsBatchEqualTo(m_renderers[j]))
					break;
				batchEnd = j;
			}

			// accumulate the current vertex start index
			for (unsigned int i = lastBatchBegin; i < batchBegin; i++)
				vaoStartIndex += m_renderers[i]->GetMesh()->GetVertexData()->size();

			// set batch texture
			const Renderer* prototype = m_renderers[batchBegin];
			if (prototype->GetTexture() != NULL)
				prototype->GetTexture()->Bind();

			// set batch shader
			prototype->GetShader()->Use();
			prototype->GetShader()->SetUniform("u_sSampler", 0);

			// set batch position attribute
			int positionAttribLocation = prototype->GetShader()->GetAttributeLocation("a_vPosition");
			glEnableVertexAttribArray(positionAttribLocation);
			glVertexAttribPointer(positionAttribLocation, 2, GL_FLOAT, GL_FALSE, prototype->GetMesh()->GetVertexSize() * sizeof(GLfloat), &(m_vertexArray[vaoStartIndex]));

			// set batch texture coordinate attribute
			if (prototype->GetTexture() != NULL)
			{
				int texCoordAttribLocation = prototype->GetShader()->GetAttributeLocation("a_vTexCoord");
				glEnableVertexAttribArray(texCoordAttribLocation);
				glVertexAttribPointer(texCoordAttribLocation, 2, GL_FLOAT, GL_FALSE, prototype->GetMesh()->GetVertexSize() * sizeof(GLfloat), &(m_vertexArray[vaoStartIndex + 2]));
			}

			// draw batched
			unsigned int numIndices = prototype->GetMesh()->GetIndices()->size();
			glDrawElements(GL_TRIANGLES, (batchEnd - batchBegin + 1) * numIndices, GL_UNSIGNED_SHORT, &m_indexArray[batchBegin * numIndices]);

			// cleanup batch
			prototype->GetShader()->Unuse();
			if (prototype->GetTexture() != NULL)
				glDisableVertexAttribArray(prototype->GetShader()->GetAttributeLocation("a_vTexCoord"));
			glDisableVertexAttribArray(positionAttribLocation);

			lastBatchBegin = batchBegin;
			batchBegin = batchEnd;
		}

		// cleanup
		glDisable(GL_BLEND);
	}

	void RenderDevice::UpdateVertexArray()
	{
		Matrix3 vpMatrix = Camera::GetInstance()->GetProjectionMatrix() * Camera::GetInstance()->GetViewMatrix();

		m_vertexArray.clear();
		ReserveVertexArray();

		unsigned int current = 0;
		for (unsigned int i = 0; i < m_renderers.size(); i++)
		{
			Mesh_v2* mesh = m_renderers[i]->GetMesh();
			const std::vector<GLfloat>* mvd = mesh->GetVertexData();
			Entity* entity = m_renderers[i]->GetParent();
			Matrix3 mvpMatrix = vpMatrix * entity->GetTransform()->GetModelMatrix();

			m_vertexArray.insert(m_vertexArray.end(), mvd->begin(), mvd->end());

			// apply transformation in vertex array
			for (unsigned int j = 0; j < mesh->GetNumVertices(); j++)
			{
				Vector2D pos = mvpMatrix * Vector2D(m_vertexArray[current], m_vertexArray[current + 1]);
				// Vector2D pos = Vector2D(m_vertexArray[current], m_vertexArray[current + 1]);
				m_vertexArray[current] = pos.GetX();
				m_vertexArray[current + 1] = pos.GetY();
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
			GLushort valueOffset = 0;
			for (unsigned int i = 0; i < m_renderers.size(); i++)
			{
				// reset value offet when switching batch
				if (i == 0 || !m_renderers[i]->IsBatchEqualTo(m_renderers[i - 1]))
					valueOffset = 0;

				Mesh_v2* mesh = m_renderers[i]->GetMesh();
				for (unsigned int j = 0; j < mesh->GetIndices()->size(); j++)
				{
					GLushort value = valueOffset + mesh->GetIndices()->at(j);
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
			if (renderer->IsBatchEqualTo(m_renderers[i]))
				return i;
		}

		return m_renderers.size();
	}

}

