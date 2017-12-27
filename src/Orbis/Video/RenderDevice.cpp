#include "RenderDevice.h"

#include "Mesh.h"
#include "Shader.h"
#include "VideoManager.h"

#include "../Components/Camera.h"
using namespace Components;

#define ORBIS_DEBUG_RENDER_DEVICE

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
		#ifdef ORBIS_DEBUG_RENDER_DEVICE
			int count = 0;
		#endif
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

			// set batch position attribute
			int positionAttribLocation = prototype->GetMaterial()->GetShader()->GetAttributeLocation("a_vPosition");
			glEnableVertexAttribArray(positionAttribLocation);
			glVertexAttribPointer(positionAttribLocation, 2, GL_FLOAT, GL_FALSE, prototype->GetMesh()->GetVertexSize() * sizeof(GLfloat), &(m_vertexArray[vaoStartIndex]));

			// set batch texture coordinate attribute
			if (prototype->GetMaterial()->GetTexture() != NULL)
			{
				int texCoordAttribLocation = prototype->GetMaterial()->GetShader()->GetAttributeLocation("a_vTexCoord");
				glEnableVertexAttribArray(texCoordAttribLocation);
				glVertexAttribPointer(texCoordAttribLocation, 2, GL_FLOAT, GL_FALSE, prototype->GetMesh()->GetVertexSize() * sizeof(GLfloat), &(m_vertexArray[vaoStartIndex + 2]));
			}

			// draw batched
			unsigned int numIndices = prototype->GetMesh()->GetIndices()->size();
			glDrawElements(GL_TRIANGLES, (batchEnd - batchBegin + 1) * numIndices, GL_UNSIGNED_SHORT, &m_indexArray[batchBegin * numIndices]);

			// cleanup batch
			prototype->GetMaterial()->GetShader()->Unuse();
			if (prototype->GetMaterial()->GetTexture() != NULL)
				glDisableVertexAttribArray(prototype->GetMaterial()->GetShader()->GetAttributeLocation("a_vTexCoord"));
			glDisableVertexAttribArray(positionAttribLocation);

			lastBatchBegin = batchBegin;
			batchBegin = batchEnd;

			#ifdef ORBIS_DEBUG_RENDER_DEVICE
				count++;
			#endif ORBIS_DEBUG_RENDER_DEVICE
		}

		#ifdef ORBIS_DEBUG_RENDER_DEVICE
			std::cout << count << std::endl;
		#endif ORBIS_DEBUG_RENDER_DEVICE

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
			Mesh* mesh = m_renderers[i]->GetMesh();
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
				if (i == 0 || !m_renderers[i]->GetMaterial()->IsBatchEqualTo(m_renderers[i - 1]->GetMaterial()))
					valueOffset = 0;

				Mesh* mesh = m_renderers[i]->GetMesh();
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
			if (renderer->GetMaterial()->IsBatchEqualTo(m_renderers[i]->GetMaterial()))
				return i;
		}

		return m_renderers.size();
	}

}

