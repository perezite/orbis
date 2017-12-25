#pragma once

#include "Transform_v2.h"

#include "../Libraries/GL.h"
#include "../Video/Mesh_v2.h"
#include "../Video/Shader_v2.h"
#include "../Video/Texture.h"
using namespace Video;

namespace Game
{
	struct Entity_v2
	{
		Transform_v2 transform;

		Shader_v2* shader;

		Texture* texture;

		Mesh_v2* mesh;

		bool isGrowing;
	};
}