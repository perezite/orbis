#pragma once

// set this define to enable exceptions for non performance critical GL calls
#define GL_NORMAL_EXCEPTIONS

// set this define to enable exceptions for all GL calls, including performance critital ones. Only use in debug mode!
#ifdef _DEBUG
	#define GL_SLOW_EXCEPTIONS
#endif

#ifdef __ANDROID__
#include <GLES2/gl2.h>	
#include <GLES2/gl2ext.h>
#endif 
#ifdef WIN32
#include <gl/glew.h>
#include <SDL2/SDL_opengl.h>
#include <gl/glu.h>
#endif

namespace Libraries
{
	// wrapper class for OpenGL calls
	class GL
	{
	public:
		// clear color
		static void ClearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

		// generate textures
		static void GenerateTextures(GLsizei n, GLuint * textures);
	};
}