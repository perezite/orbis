#pragma once

#include "Color.h"
#include "RenderMode.h"

#include "../../Base/Math/Vector2D.h"
using namespace Math;

#ifdef __ANDROID__
#include <GLES2/gl2.h>	
#include <GLES2/gl2ext.h>
#endif 
#ifdef WIN32
#include <gl/glew.h>
#include <SDL2/SDL_opengl.h>
#endif

#include <string>
#include <vector>

namespace Video
{
	class Shader
	{
	public:
		// ctor
		Shader();

		// dtor
		~Shader();

		// get the position location within the vertex shader
		int GetPositionLocation();

		// enable the shader
		void Use();

		// disable the shader
		void Unuse();
	};
}