#pragma once

#include "Transform_v2.h"

#include "../Libraries/GL.h"
#include "../Video/Mesh_v2.h"
#include "../Video/Texture.h"
using namespace Video;

namespace Game
{
	struct Entity_v2
	{
		Transform_v2 transform;

		Texture* texture;

		Mesh_v2* mesh;

		bool isGrowing;
	};
}