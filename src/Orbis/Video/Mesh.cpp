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

	void Mesh::getTransformedVertexData(Transform* trans, Texture* tex, std::vector<float>& result)
	{
		// compute mvp matrix
		const Matrix3& camMatrix = Camera::getInstance()->getCamMatrix(trans->transformSpace);
		Matrix3 mvpMatrix = camMatrix * trans->getModelMatrix();

		// compute transformed vertex data
		result = *getVertexData();
		for (unsigned int i = 0; i < getNumVertices(); i++)
		{
			unsigned int start = i * getVertexCount();
			Vector2D pos = mvpMatrix * Vector2D(result[start + 0], result[start + 1]);
			result[start + 0] = pos.x; result[start + 1] = pos.y;
			if (tex) {
				Vector2D uvCoord = tex->mapUVCoord(Vector2D(result[start + 2], result[start + 3]));
				result[start + 2] = uvCoord.x; result[start + 3] = uvCoord.y;
			}
		}
	}
}