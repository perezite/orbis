#include "Mesh.h"

#include "VideoManager.h"
#include "../Components/Camera.h"


namespace orb
{
	Mesh* Mesh::createVertexColoredTexturedQuad(Color color)
	{
		Mesh* mesh = new Mesh(
		{
			-0.5, -0.5, 0.0f, 0.0f,	color.r, color.g, color.b, color.a,		// left bottom
			0.5, -0.5, 1.0f, 0.0f, color.r, color.g, color.b, color.a,		// right bottom
			-0.5,  0.5, 0.0f, 1.0f, color.r, color.g, color.b, color.a,		// left top
			0.5,  0.5, 1.0f, 1.0f, color.r, color.g, color.b, color.a		// right top
		},
			8,
			{ 0, 1, 2, 2, 1, 3 },
			true
		);

		return mesh;
	}

	Mesh* Mesh::createTexturedQuad()
	{
		Mesh* mesh = new Mesh(
		{
			-0.5, -0.5, 0.0f, 0.0f,		// left bottom
			0.5, -0.5, 1.0f, 0.0f,		// right bottom
			-0.5,  0.5, 0.0f, 1.0f,		// left top
			0.5,  0.5, 1.0f, 1.0f		// right top
		},
			4,
			{ 0, 1, 2, 2, 1, 3 }
		);

		return mesh;
	}

	Mesh* Mesh::createFlatQuad()
	{
		Mesh* mesh = new Mesh(
		{
			-0.5, -0.5,					// left bottom
			0.5, -0.5,					// right bottom
			-0.5,  0.5, 				// left top
			0.5,  0.5					// right top
		},
			2,
			{ 0, 1, 2, 2, 1, 3 }
		);

		return mesh;
	}

	const void Mesh::computeIndices(std::vector<GLushort>& result, unsigned int offset) const
	{
		result = m_indices;
		for (unsigned int i = 0; i < result.size(); i++)
			result[i] += offset;
	}

	void Mesh::computeTransformedVertices(std::vector<float>& result, Transform* transform, Texture* tex)
	{
		// compute mvp matrix
		Camera* cam = Camera::instance();
		Matrix3 camMatrix = cam->getCamMatrix(transform->transformSpace);
		Matrix3 mvpMatrix = camMatrix * transform->getModelMatrix();

		// compute transformed vertex data
		result = *getVertexData();
		for (unsigned int i = 0; i < getNumVertices(); i++)
		{
			unsigned int start = i * getVertexCount();
			Vector2f pos = mvpMatrix * Vector2f(result[start + 0], result[start + 1]);
			result[start + 0] = pos.x; result[start + 1] = pos.y;
			if (tex) {
				Vector2f uvCoord = tex->mapUVCoord(Vector2f(result[start + 2], result[start + 3]));
				result[start + 2] = uvCoord.x; result[start + 3] = uvCoord.y;
			}
		}
	}
}