#include "RenderDevice_v2.h"

namespace Video
{
	const int RenderDevice_v2::INDICES_PER_SPRITE = 6;
	const int RenderDevice_v2::NUM_SPRITES = 1000;
	const int RenderDevice_v2::VERTICES_PER_SPRITE = 4;

	void RenderDevice_v2::Render(GLuint shaderProgram, GLint samplerHandle, GLint positionHandle, GLint texCoordHandle, std::vector<GLfloat>& vertices, const std::vector<GLushort>& indices, const std::vector<Entity_v2>& entities)
	{
		// set states
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// set shader
		glUseProgram(shaderProgram);
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(samplerHandle, 0);

		// set arrays
		UpdateVertices(vertices, entities);
		glEnableVertexAttribArray(positionHandle);
		glEnableVertexAttribArray(texCoordHandle);
		glVertexAttribPointer(positionHandle, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), &(vertices[0]));
		glVertexAttribPointer(texCoordHandle, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), &(vertices[2]));

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
			glBindTexture(GL_TEXTURE_2D, entities[batchBegin].texture);

			// draw
			glDrawElements(GL_TRIANGLES, (batchEnd - batchBegin + 1) * INDICES_PER_SPRITE, GL_UNSIGNED_SHORT, &indices[batchBegin * INDICES_PER_SPRITE]);
			batchBegin = batchEnd;
		}

		// cleanup
		glDisableVertexAttribArray(texCoordHandle);
		glDisableVertexAttribArray(positionHandle);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
		glUseProgram(0);
	}

	void RenderDevice_v2::UpdateVertices(std::vector<GLfloat>& vertices, const std::vector<Entity_v2>& entities)
	{
		std::vector<GLfloat> quad = {
			-1, -1, 0.0f, 0.0f,	// left bottom
			1, -1, 1.0f, 0.0f,	// right bottom
			-1,  1, 0.0f, 1.0f,	// left top
			1,  1, 1.0f, 1.0f	// right top
		};

		vertices.clear();
		vertices.reserve(NUM_SPRITES * quad.size());
		for (int i = 0; i < NUM_SPRITES; i++)
		{
			vertices.insert(vertices.end(), quad.begin(), quad.end());

			// apply scale
			for (unsigned int j = 0; j < quad.size() / VERTICES_PER_SPRITE; j++)
			{
				vertices[i * quad.size() + j * VERTICES_PER_SPRITE] *= entities[i].extent;
				vertices[i * quad.size() + j * VERTICES_PER_SPRITE] += entities[i].positionX;
				vertices[i * quad.size() + j * VERTICES_PER_SPRITE + 1] *= entities[i].extent;
				vertices[i * quad.size() + j * VERTICES_PER_SPRITE + 1] += entities[i].positionY;
			}
		}
	}
}
