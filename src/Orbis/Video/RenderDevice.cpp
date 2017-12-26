#include "RenderDevice.h"

#include "Mesh_v2.h"
#include "Shader.h"
#include "VideoManager.h"

#include "../Components/Camera.h"
using namespace Components;

namespace Video
{
	void RenderDevice::Render(const std::vector<Entity_v2>& entities)
	{
		std::vector<GLfloat>& vertexArray = VideoManager::GetInstance()->GetVertexArray();
		std::vector<GLushort>& indexArray = VideoManager::GetInstance()->GetIndexArray();

		// set states
		glActiveTexture(GL_TEXTURE0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// update vertices
		UpdateVertices(vertexArray, entities);

		// render batched
		for (unsigned int batchBegin = 0; batchBegin < entities.size(); batchBegin++)
		{
			// compute batch indices
			unsigned int batchEnd = batchBegin;
			for (unsigned int j = batchBegin; j < entities.size(); j++)
			{
				if (entities[j].texture != entities[batchBegin].texture)
					break;
				batchEnd = j;
			}

			// set texture
			const Entity_v2& batchEntity = entities[batchBegin];
			if (batchEntity.texture != NULL)
				batchEntity.texture->Bind();

			// set shader
			batchEntity.shader->Use();
			batchEntity.shader->SetUniform("u_sSampler", 0);

			// set position attribute
			int positionAttribLocation = batchEntity.shader->GetAttributeLocation("a_vPosition");
			glEnableVertexAttribArray(positionAttribLocation);
			glVertexAttribPointer(positionAttribLocation, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), &(vertexArray[0]));

			// set texture coordinate attribute
			if (batchEntity.texture != NULL)
			{
				int texCoordAttribLocation = batchEntity.shader->GetAttributeLocation("a_vTexCoord");
				glEnableVertexAttribArray(texCoordAttribLocation);
				glVertexAttribPointer(texCoordAttribLocation, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), &(vertexArray[2]));
			}

			// draw
			unsigned int numIndices = batchEntity.mesh->GetIndices()->size();
			glDrawElements(GL_TRIANGLES, (batchEnd - batchBegin + 1) * numIndices, GL_UNSIGNED_SHORT, &indexArray[batchBegin * numIndices]);

			// cleanup
			batchEntity.shader->Unuse();
			if (batchEntity.texture != NULL)
				glDisableVertexAttribArray(batchEntity.shader->GetAttributeLocation("a_vTexCoord"));
			glDisableVertexAttribArray(positionAttribLocation);

			batchBegin = batchEnd;
		}

		// cleanup
		glDisable(GL_BLEND);
	}

	void RenderDevice::UpdateVertices(std::vector<GLfloat>& vertices, const std::vector<Entity_v2>& entities)
	{
		Matrix3 vpMatrix = Camera::GetInstance()->GetProjectionMatrix() * Camera::GetInstance()->GetViewMatrix();
		Mesh_v2* mesh = Mesh_v2::GetTexturedQuad();
		const std::vector<GLfloat>* quad = mesh->GetVertexData();

		vertices.clear();
		vertices.reserve(entities.size() * quad->size());
		for (unsigned int i = 0; i < entities.size(); i++)
		{
			Matrix3 mvpMatrix = vpMatrix * entities[i].transform.GetModelMatrix();
			vertices.insert(vertices.end(), quad->begin(), quad->end());

			// apply transformation
			for (unsigned int j = 0; j < quad->size() / mesh->GetNumVertices(); j++)
			{
				int index = i * quad->size() + j * entities[i].mesh->GetNumVertices();
				Vector2D vertex = mvpMatrix * Vector2D(vertices[index], vertices[index + 1]);
				vertices[index] = vertex.GetX();
				vertices[index + 1] = vertex.GetY();
			}
		}
	}
}

