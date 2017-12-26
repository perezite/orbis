#include "RenderDevice.h"

#include "Mesh_v2.h"
#include "Shader.h"
#include "VideoManager.h"

#include "../Components/Camera.h"
using namespace Components;

namespace Video
{
	void RenderDevice::Render()
	{
		std::vector<Renderer*>& renderers = VideoManager::GetInstance()->GetRenderers();
		std::vector<GLfloat>& vertexArray = VideoManager::GetInstance()->GetVertexArray();
		std::vector<GLushort>& indexArray = VideoManager::GetInstance()->GetIndexArray();

		// set states
		glActiveTexture(GL_TEXTURE0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// update arrays
		VideoManager::GetInstance()->UpdateIndexArray();
		UpdateVertices(vertexArray, renderers);

		// render batched
		for (unsigned int batchBegin = 0; batchBegin < renderers.size(); batchBegin++)
		{
			// compute batch indices
			unsigned int batchEnd = batchBegin;
			for (unsigned int j = batchBegin; j < renderers.size(); j++)
			{
				if (!renderers[batchBegin]->IsBatchEqualTo(renderers[j]))
					break;
				batchEnd = j;
			}

			// set batch texture
			const Renderer* prototype = renderers[batchBegin];
			if (prototype->GetTexture() != NULL)
				prototype->GetTexture()->Bind();

			// set batch shader
			prototype->GetShader()->Use();
			prototype->GetShader()->SetUniform("u_sSampler", 0);

			// set batch position attribute
			int positionAttribLocation = prototype->GetShader()->GetAttributeLocation("a_vPosition");
			glEnableVertexAttribArray(positionAttribLocation);
			glVertexAttribPointer(positionAttribLocation, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), &(vertexArray[0]));

			// set batch texture coordinate attribute
			if (prototype->GetTexture() != NULL)
			{
				int texCoordAttribLocation = prototype->GetShader()->GetAttributeLocation("a_vTexCoord");
				glEnableVertexAttribArray(texCoordAttribLocation);
				glVertexAttribPointer(texCoordAttribLocation, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), &(vertexArray[2]));
			}

			// draw batched
			unsigned int numIndices = prototype->GetMesh()->GetIndices()->size();
			glDrawElements(GL_TRIANGLES, (batchEnd - batchBegin + 1) * numIndices, GL_UNSIGNED_SHORT, &indexArray[batchBegin * numIndices]);

			// cleanup batch
			prototype->GetShader()->Unuse();
			if (prototype->GetTexture() != NULL)
				glDisableVertexAttribArray(prototype->GetShader()->GetAttributeLocation("a_vTexCoord"));
			glDisableVertexAttribArray(positionAttribLocation);

			batchBegin = batchEnd;
		}

		// cleanup
		glDisable(GL_BLEND);
	}

	void RenderDevice::UpdateVertices(std::vector<GLfloat>& vertices, const std::vector<Renderer*>& renderers)
	{
		Matrix3 vpMatrix = Camera::GetInstance()->GetProjectionMatrix() * Camera::GetInstance()->GetViewMatrix();
		Mesh_v2* mesh = Mesh_v2::GetTexturedQuad();
		const std::vector<GLfloat>* quad = mesh->GetVertexData();

		vertices.clear();
		ReserveVertexArray(vertices, renderers);

		for (unsigned int i = 0; i < renderers.size(); i++)
		{
			Entity* entity = renderers[i]->GetParent();
			Matrix3 mvpMatrix = vpMatrix * entity->GetTransform()->GetModelMatrix();
			vertices.insert(vertices.end(), quad->begin(), quad->end());

			// apply transformation in vertex array
			for (unsigned int j = 0; j < quad->size() / mesh->GetNumVertices(); j++)
			{
				int index = i * quad->size() + j * renderers[i]->GetMesh()->GetNumVertices();
				Vector2D vertex = mvpMatrix * Vector2D(vertices[index], vertices[index + 1]);
				vertices[index] = vertex.GetX();
				vertices[index + 1] = vertex.GetY();
			}
		}
	}

	void RenderDevice::ReserveVertexArray(std::vector<GLfloat>& vertexArray, const std::vector<Renderer*>& renderers)
	{
		unsigned int vertexArraySize = 0;
		for (unsigned int i = 0; i < renderers.size(); i++)
		{
			vertexArraySize += renderers[i]->GetMesh()->GetNumVertices();
		}

		vertexArray.reserve(vertexArraySize);
	}
}

