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
	#if defined(NORMAL_GL_CHECKS) || defined(DIAGNOSTIC_GL_CHECKS)
		#define CHECK_GL() \
			CheckGLError();
	#else
		#define	CHECK_GL();
	#endif

	// faster version of handling GL errors which only only does error checks if DIAGNOSTIC_GL_CHECKS is defined
	#if defined(DIAGNOSTIC_GL_CHECKS)
		#define DIAGNOSTIC_CHECK_GL() \
			CheckGLError();
	#else
		#define DIAGNOSTIC_CHECK_GL();
	#endif

}

namespace Libraries
{
	void GL::ClearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
	{
		glClearColor(r, g, b, a);
		DIAGNOSTIC_CHECK_GL()
	}

	void GL::Clear(GLbitfield mask)
	{
		glClear(mask);
		DIAGNOSTIC_CHECK_GL();
	}

	void GL::GenerateTextures(GLsizei n, GLuint* textures)
	{
		glGenTextures(n, textures);
		CHECK_GL();
	}

	void GL::GenerateBuffers(GLsizei n, GLuint * buffers)
	{
		glGenBuffers(n, buffers);
		CHECK_GL();
	}

	void GL::BindTexture(GLenum target, GLuint texture)
	{
		glBindTexture(target, texture);
		DIAGNOSTIC_CHECK_GL();
	}

	void GL::TextureImage2D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* data)
	{
		glTexImage2D(target, level, internalFormat, width, height, border, format, type, data);
		CHECK_GL();
	}

	void GL::TextureParameter(GLenum target, GLenum pname, GLint param)
	{
		glTexParameteri(target, pname, param);
		DIAGNOSTIC_CHECK_GL();
	}

	void GL::BindBuffer(GLenum target, GLuint buffer)
	{
		glBindBuffer(target, buffer);
		DIAGNOSTIC_CHECK_GL();
	}

	void GL::BufferData(GLenum target, GLsizeiptr size, const GLvoid * data, GLenum usage)
	{
		glBufferData(target, size, data, usage);
		DIAGNOSTIC_CHECK_GL();
	}

	void GL::VertexAttributePointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer)
	{
		glVertexAttribPointer(index, size, type, normalized, stride, pointer);
		DIAGNOSTIC_CHECK_GL();
	}

	void GL::Enable(GLenum cap)
	{
		glEnable(cap);
		DIAGNOSTIC_CHECK_GL();
	}

	void GL::Disable(GLenum cap)
	{
		glDisable(cap);
		DIAGNOSTIC_CHECK_GL();
	}

	void GL::BlendFunction(GLenum sfactor, GLenum dfactor)
	{
		glBlendFunc(sfactor, dfactor);
		DIAGNOSTIC_CHECK_GL();
	}

	void GL::ActiveTexture(GLenum texture)
	{
		glActiveTexture(texture);
		DIAGNOSTIC_CHECK_GL();
	}

	void GL::EnableVertexAttributeArray(GLuint index)
	{
		glEnableVertexAttribArray(index);
		DIAGNOSTIC_CHECK_GL();
	}

	void GL::DisableVertexAttribArray(GLuint index)
	{
		glDisableVertexAttribArray(index);
		DIAGNOSTIC_CHECK_GL();
	}

	void GL::DrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid * indices)
	{
		glDrawElements(mode, count, type, indices);
		DIAGNOSTIC_CHECK_GL();
	}

	GLuint GL::CreateShader(GLenum shaderType)
	{
		GLuint handle = glCreateShader(shaderType);
		if (handle == 0)
			CheckGLError();
		return handle;
	}

	void GL::ShaderSource(GLuint shader, GLsizei count, const GLchar** string, const GLint * length)
	{
		glShaderSource(shader, count, string, length);
		CHECK_GL();
	}

	void GL::CompileShader(GLuint shader)
	{
		glCompileShader(shader);
		CHECK_GL();
	}

	void GL::GetShaderParameter(GLuint shader, GLenum pname, GLint * params)
	{
		glGetShaderiv(shader, pname, params);
		CHECK_GL();
	}

	void GL::GetShaderInfoLog(GLuint shader, GLsizei maxLength, GLsizei * length, GLchar * infoLog)
	{
		glGetShaderInfoLog(shader, maxLength, length, infoLog);
		CHECK_GL();
	}

	void GL::DeleteShader(GLuint shader)
	{
		glDeleteShader(shader);
		CHECK_GL();
	}

	void GL::LinkProgram(GLuint program)
	{
		glLinkProgram(program);
		CHECK_GL();
	}

	void GL::GetProgramParameter(GLuint program, GLenum pname, GLint * params)
	{
		glGetProgramiv(program, pname, params);
		CHECK_GL();
	}

	void GL::GetProgramInfoLog(GLuint program, GLsizei maxLength, GLsizei * length, GLchar * infoLog)
	{
		glGetProgramInfoLog(program, maxLength, length, infoLog);
		CHECK_GL();
	}

	void GL::DeleteProgram(GLuint program)
	{
		glDeleteProgram(program);
		CHECK_GL();
	}

	GLuint GL::CreateProgram()
	{
		GLuint handle = glCreateProgram();
		if (handle == 0)
			CheckGLError();
		return handle;
	}

	void GL::UseProgram(GLuint program)
	{
		glUseProgram(program);
		DIAGNOSTIC_CHECK_GL();
	}

	void GL::AttachShader(GLuint program, GLuint shader)
	{
		glAttachShader(program, shader);
		CHECK_GL();
	}

	GLint GL::GetAttributeLocation(GLuint program, const GLchar * name)
	{
		GLint handle = glGetAttribLocation(program, name);
		#if defined(DIAGNOSTIC_GL_CHECKS) 
			if (handle == -1)
				throw Exception(std::string(__func__) + " failed");
		#endif	
		return handle;
	}

	GLint GL::GetUniformLocation(GLuint program, const GLchar * name)
	{
		GLint handle = glGetUniformLocation(program, name);
		#if defined(DIAGNOSTIC_GL_CHECKS) 
			if (handle == -1)
				throw Exception(std::string(__func__) + " failed");
		#endif	
		return handle;
	}

	void GL::UniformMatrix4(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
	{
		glUniformMatrix4fv(location, count, transpose, value); 
		DIAGNOSTIC_CHECK_GL();
	}

	void GL::Uniform(GLint location, GLint v0)
	{
		glUniform1i(location, v0);
		DIAGNOSTIC_CHECK_GL();
	}
}
