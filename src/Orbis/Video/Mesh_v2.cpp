#include "Mesh_v2.h"

namespace Video
{
	Mesh_v2* Mesh_v2::GetTexturedQuad()
	{
		static Mesh_v2 texturedQuad(
			{	
				-1, -1, 0.0f, 0.0f,		// left bottom
				 1, -1, 1.0f, 0.0f,		// right bottom
				-1,  1, 0.0f, 1.0f,		// left top
				 1,  1, 1.0f, 1.0f		// right top
			},
			4,
			{ 0, 1, 2, 2, 1, 3 }
		);

		return &texturedQuad;
	}

	Mesh_v2* Mesh_v2::GetFlatQuad()
	{
		static Mesh_v2 flatQuad(
			{
				-1, -1,					// left bottom
				 1, -1,					// right bottom
				-1,  1, 				// left top
				 1,  1					// right top
			},
			2,
			{ 0, 1, 2, 2, 1, 3 }
		);

		return &flatQuad;
	}
}