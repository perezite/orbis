#include "Mesh.h"

#include "VideoManager.h"

namespace Video
{
	Mesh* Mesh::GetTexturedQuad()
	{
		static Mesh texturedQuad(
			{
				-0.5, -0.5, 0.0f, 0.0f,		// left bottom
				 0.5, -0.5, 1.0f, 0.0f,		// right bottom
				-0.5,  0.5, 0.0f, 1.0f,		// left top
				 0.5,  0.5, 1.0f, 1.0f		// right top
			},
			4,
			{ 0, 1, 2, 2, 1, 3 }
		);

		return &texturedQuad;
	}

	Mesh* Mesh::GetFlatQuad()
	{
		static Mesh flatQuad(
			{
				-0.5, -0.5,					// left bottom
				 0.5, -0.5,					// right bottom
				-0.5,  0.5, 				// left top
				 0.5,  0.5					// right top
			},
			2,
			{ 0, 1, 2, 2, 1, 3 }
		);

		return &flatQuad;
	}
}