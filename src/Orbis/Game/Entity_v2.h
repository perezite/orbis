#pragma once

#include "Transform.h"

#include "../Libraries/GL.h"
#include "../Video/Mesh_v2.h"
#include "../Video/Shader.h"
#include "../Video/Texture.h"
using namespace Video;

namespace Game
{
	struct Entity_v2
	{
		Transform transform;

		Shader* shader;

		Texture* texture;

		Mesh_v2* mesh;

		bool isGrowing;
	};
}