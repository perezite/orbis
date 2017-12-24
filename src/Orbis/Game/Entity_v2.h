#pragma once

#include "../Libraries/GL.h"

namespace Game
{
	struct Entity_v2
	{
		float positionX;
		float positionY;
		float extent;
		bool isGrowing;
		GLuint texture;
	};
}