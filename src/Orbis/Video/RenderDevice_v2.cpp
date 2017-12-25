#include "RenderDevice_v2.h"

#include "Mesh_v2.h"
#include "Shader.h"

#include "../Components/Camera_v2.h"
using namespace Components;

namespace Video
{
	const int RenderDevice_v2::INDICES_PER_SPRITE = 6;
	const int RenderDevice_v2::VERTICES_PER_SPRITE = 4;

	void RenderDevice_v2::Render(Shader_v2* shader, std::vector<GLfloat>& vertices, const std::vector<GLushort>& indices, const std::vector<Entity_v2>& entities)
	{
		int positionAttribHandle = shader->GetAttributeHandle("a_vPosition");
		int texCoordAttribHandle = shader->GetAttributeHandle("a_vTexCoord");

		// set states
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// set shader
		shader->Use();
		glActiveTexture(GL_TEXTURE0);
		shader->SetUniform("u_sSampler", 0);

		// set arrays
		UpdateVertices(vertices, entities);
		glEnableVertexAttribArray(positionAttribHandle);
		glEnableVertexAttribArray(texCoordAttribHandle);
		glVertexAttribPointer(positionAttribHandle, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), &(vertices[0]));
		glVertexAttribPointer(texCoordAttribHandle, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), &(vertices[2]));

		// render batched 
		for (unsigned int batchBegin = 0; batchBegin < entities.size(); batchBegin++)
		{
			// compute batch
			unsigned int batchEnd = batchBegin;
			for (unsigned int j = batchBegin; j < entities.size(); j++)
			{
				if (entities[j].texture != entities[batchBegin].texture)
					break;
				batchEnd = j;
			}

			// set texture
			entities[batchBegin].texture->Bind();

			// draw
			glDrawElements(GL_TRIANGLES, (batchEnd - batchBegin + 1) * INDICES_PER_SPRITE, GL_UNSIGNED_SHORT, &indices[batchBegin * INDICES_PER_SPRITE]);
			batchBegin = batchEnd;
		}

		// cleanup
		glDisableVertexAttribArray(texCoordAttribHandle);
		glDisableVertexAttribArray(positionAttribHandle);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
		shader->Unuse();
	}

	void RenderDevice_v2::UpdateVertices(std::vector<GLfloat>& vertices, const std::vector<Entity_v2>& entities)
	{
		Matrix3 vpMatrix = Camera_v2::GetInstance()->GetProjectionMatrix() * Camera_v2::GetInstance()->GetViewMatrix();
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
				int index = i * quad->size() + j * VERTICES_PER_SPRITE;
				Vector2D vertex = mvpMatrix * Vector2D(vertices[index], vertices[index + 1]);
				vertices[index] = vertex.GetX();
				vertices[index + 1] = vertex.GetY();
			}
		}
	}
}
