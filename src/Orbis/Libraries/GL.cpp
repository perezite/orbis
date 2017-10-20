#include "GL.h"

#include "../../Base/System/Exception.h"
#include "../../Base/System/StringHelper.h"
using namespace System;

namespace {
	// handle GL errors
	void CheckGLError()
	{
		GLenum error = glGetError();
		if (error != GL_NO_ERROR)									
		{	
			std::string message = StringHelper::GetFormattedString("OpenGL Error: Error Code %d", 1024, error);
			throw Exception(message);	
		}
	}

	// handle GL errors
	#if defined(GL_NORMAL_EXCEPTIONS) || defined(GL_SLOW_EXCEPTIONS)
		#define GL_VERIFY() \
			CheckGLError();
	#else
		#define	GL_VERIFY();
	#endif

	// handle GL errors even in performance critical functions
	#if defined(GL_SLOW_EXCEPTIONS)
		#define GL_SLOW_VERIFY() \
			CheckGLError();
	#else
		#define GL_SLOW_VERIFY();
	#endif

}

namespace Libraries
{
	void GL::ClearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
	{
		glClearColor(r, g, b, a);
		GL_SLOW_VERIFY()
	}

	void GL::GenerateTextures(GLsizei n, GLuint* textures)
	{
		glGenTextures(n, textures);
		GL_VERIFY();
	}
}
