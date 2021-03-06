#include "GL.h"

#include "../../Base/Base.h"
using namespace base;

void GL_dummy()
{
	return;
}

#if defined(ORBIS_DEBUG_GL)

void GL_Verify(void)
	{
		GLenum err;

		while ((err = glGetError()) != GL_NO_ERROR)
		{
			std::string message = StringUtil::getFormatted("OpenGL Error: Error Code %d", 1024, err);
			throw Exception(message);
		}
	}

	GLuint GL_Verify(GLuint returnValue)
	{
		if (returnValue == 0)
			GL_Verify();

		return returnValue;
	}

	GLint GL_Verify(GLint returnValue)
	{
		if (returnValue < 0)
			GL_Verify();

		return returnValue;
	}

	#if defined(WIN32)
		GLenum GLEW_Verify(GLenum returnValue)
		{
			if (returnValue != GLEW_OK)
			{
				std::string message = StringUtil::getFormatted("GLEW Error: Error Code %s", 1024, glewGetErrorString(returnValue));
				throw Exception(message);
			}

			return returnValue;
		}
	#endif

#endif
