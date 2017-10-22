#include "GL.h"

#include "../../Base/System/Exception.h"
#include "../../Base/System/StringHelper.h"
using namespace System;

namespace {
	// handle GL errors
	#if defined(GL_NORMAL_EXCEPTIONS) || defined(GL_DIAGNOSTIC_EXCEPTIONS)
		void CheckGLError()
		{
			GLenum error = glGetError();
			if (error != GL_NO_ERROR)									
			{	
				std::string message = StringHelper::GetFormattedString("OpenGL Error: Error Code %d", 1024, error);
				throw Exception(message);	
			}
		}
	#endif

	// handle GL errors
	#if defined(GL_NORMAL_EXCEPTIONS) || defined(GL_DIAGNOSTIC_EXCEPTIONS)
		#define GL_VERIFY() \
			CheckGLError();
	#else
		#define	GL_VERIFY();
	#endif

	// faster version of handling GL errors which only only does error checks if GL_DIAGNOSTIC_EXCEPTIONS is defined
	#if defined(GL_DIAGNOSTIC_EXCEPTIONS)
		#define GL_FAST_VERIFY() \
			CheckGLError();
	#else
		#define GL_FAST_VERIFY();
	#endif

}

namespace Libraries
{
	void GL::ClearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
	{
		glClearColor(r, g, b, a);
		GL_FAST_VERIFY()
	}

	void GL::Clear(GLbitfield mask)
	{
		glClear(mask);
		GL_FAST_VERIFY();
	}

	void GL::GenerateTextures(GLsizei n, GLuint* textures)
	{
		glGenTextures(n, textures);
		GL_VERIFY();
	}

	void GL::GenerateBuffers(GLsizei n, GLuint * buffers)
	{
		glGenBuffers(n, buffers);
		GL_VERIFY();
	}

	void GL::BindTexture(GLenum target, GLuint texture)
	{
		glBindTexture(target, texture);
		GL_FAST_VERIFY();
	}

	void GL::TextureImage2D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* data)
	{
		glTexImage2D(target, level, internalFormat, width, height, border, format, type, data);
		GL_VERIFY();
	}

	void GL::TextureParameter(GLenum target, GLenum pname, GLint param)
	{
		glTexParameteri(target, pname, param);
		GL_FAST_VERIFY();
	}

	void GL::BindBuffer(GLenum target, GLuint buffer)
	{
		glBindBuffer(target, buffer);
		GL_FAST_VERIFY();
	}

	void GL::BufferData(GLenum target, GLsizeiptr size, const GLvoid * data, GLenum usage)
	{
		glBufferData(target, size, data, usage);
		GL_FAST_VERIFY();
	}

	void GL::VertexAttributePointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer)
	{
		glVertexAttribPointer(index, size, type, normalized, stride, pointer);
		GL_FAST_VERIFY();
	}

	void GL::Enable(GLenum cap)
	{
		glEnable(cap);
		GL_FAST_VERIFY();
	}

	void GL::Disable(GLenum cap)
	{
		glDisable(cap);
		GL_FAST_VERIFY();
	}

	void GL::BlendFunction(GLenum sfactor, GLenum dfactor)
	{
		glBlendFunc(sfactor, dfactor);
		GL_FAST_VERIFY();
	}

	void GL::ActiveTexture(GLenum texture)
	{
		glActiveTexture(texture);
		GL_FAST_VERIFY();
	}

	void GL::EnableVertexAttributeArray(GLuint index)
	{
		glEnableVertexAttribArray(index);
		GL_FAST_VERIFY();
	}

	void GL::DisableVertexAttribArray(GLuint index)
	{
		glDisableVertexAttribArray(index);
		GL_FAST_VERIFY();
	}

	void GL::DrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid * indices)
	{
		glDrawElements(mode, count, type, indices);
		GL_FAST_VERIFY();
	}
}
