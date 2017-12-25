#include "RenderDevice_v2.h"

#include "Mesh_v2.h"
#include "Shader.h"
#include "VideoManager_v2.h"

#include "../Components/Camera_v2.h"
using namespace Components;

namespace Video
{
	void RenderDevice_v2::Render(const std::vector<Entity_v2>& entities)
	{
		Shader_v2* shader = entities[0].shader;
		std::vector<GLfloat>& vertexArray = VideoManager_v2::GetInstance()->GetVertexArray();
		std::vector<GLushort>& indexArray = VideoManager_v2::GetInstance()->GetIndexArray();

		// set states
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// set shader
		shader->Use();
		int positionAttribHandle = entities[0].shader->GetAttributeHandle("a_vPosition");
		int texCoordAttribHandle = entities[0].shader->GetAttributeHandle("a_vTexCoord");
		glActiveTexture(GL_TEXTURE0);
		shader->SetUniform("u_sSampler", 0);

		// set arrays
		UpdateVertices(vertexArray, entities);

		glEnableVertexAttribArray(positionAttribHandle);
		glEnableVertexAttribArray(texCoordAttribHandle);
		glVertexAttribPointer(positionAttribHandle, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), &(vertexArray[0]));
		glVertexAttribPointer(texCoordAttribHandle, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), &(vertexArray[2]));

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
			unsigned int numIndices = entities[batchBegin].mesh->GetIndices()->size();
			glDrawElements(GL_TRIANGLES, (batchEnd - batchBegin + 1) *numIndices, GL_UNSIGNED_SHORT, &indexArray[batchBegin * numIndices]);
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
				int index = i * quad->size() + j * entities[j].mesh->GetNumVertices();
				Vector2D vertex = mvpMatrix * Vector2D(vertices[index], vertices[index + 1]);
				vertices[index] = vertex.GetX();
				vertices[index + 1] = vertex.GetY();
			}
		}
	}
}
