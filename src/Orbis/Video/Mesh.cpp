#include "Mesh.h"

#include "VideoManager.h"

namespace video
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
}