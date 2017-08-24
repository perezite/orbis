#pragma once

#ifdef __ANDROID__
#include <GLES2/gl2.h>	
#include <GLES2/gl2ext.h>
#endif 
#ifdef WIN32
#include <gl/glew.h>
#include <SDL2/SDL_opengl.h>
#endif

namespace Video
{
	enum RenderMode
	{
		Triangle = GL_TRIANGLES
	};
}