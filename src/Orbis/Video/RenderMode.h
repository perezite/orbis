#pragma once

#include "../Libraries/GL.h"

namespace video
{
	enum class RenderMode : GLenum
	{
		Triangles = GL_TRIANGLES,
		Lines = GL_LINES
	};
}