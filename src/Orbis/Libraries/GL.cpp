#include "GL.h"

#include "../../Base/System/Exception.h"
#include "../../Base/System/StringHelper.h"
using namespace System;

#ifdef __ANDROID__
#include <GLES2/gl2.h>	
#include <GLES2/gl2ext.h>
#endif 
#ifdef WIN32
#include <gl/glew.h>
#include <SDL2/SDL_opengl.h>
#include <gl/glu.h>
#endif

namespace {
	// handle GL exceptions
	void CheckGLError()
	{
		GLenum error = glGetError();
		if (error != GL_NO_ERROR)									
		{	
			std::string message = StringHelper::GetFormattedString("OpenGL Error: Error Code %d", 1024, error);
			throw Exception(message);	
		}
	}

	// handle GL exceptions
	#ifdef GL_EXCEPTIONS
		#define GL_VERIFY() \
			CheckGLError();
	#else
		#define	GL_VERIFY();
	#endif
}

namespace Libraries
{
	void GL::ClearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
		GL_VERIFY()
	}
}
