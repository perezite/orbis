#pragma once

#include "../Libraries/GL.h"

namespace Video
{
	enum class RenderMode : GLenum
	{
		Triangles = GL_TRIANGLES,
		Lines = GL_LINES
	};
}