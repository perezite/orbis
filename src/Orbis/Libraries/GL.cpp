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

	// faster version of handling GL errors which only only does error checks if DIAGNOSTIC_GL_CHECKS is defined
	#if defined(GL_DIAGNOSTICS)
		#define GL_DIAGNOSTIC_CHECK() \
			CheckGLError();
	#else
		#define GL_DIAGNOSTIC_CHECK();
	#endif

}

namespace Libraries
{
	void GL::Temp()
	{
		GL_DIAGNOSTIC_CHECK();
	}

	void GL::ClearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
	{
		glClearColor(r, g, b, a);
		GL_DIAGNOSTIC_CHECK()
	}

	void GL::Clear(GLbitfield mask)
	{
		glClear(mask);
		GL_DIAGNOSTIC_CHECK();
	}

	void GL::GenerateTextures(GLsizei n, GLuint* textures)
	{
		glGenTextures(n, textures);
		GL_DIAGNOSTIC_CHECK();
	}

	void GL::GenerateBuffers(GLsizei n, GLuint * buffers)
	{
		glGenBuffers(n, buffers);
		GL_DIAGNOSTIC_CHECK();
	}

	void GL::BindTexture(GLenum target, GLuint texture)
	{
		glBindTexture(target, texture);
		GL_DIAGNOSTIC_CHECK();
	}

	void GL::TextureImage2D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* data)
	{
		glTexImage2D(target, level, internalFormat, width, height, border, format, type, data);
		GL_DIAGNOSTIC_CHECK();
	}

	void GL::TextureParameter(GLenum target, GLenum pname, GLint param)
	{
		glTexParameteri(target, pname, param);
		GL_DIAGNOSTIC_CHECK();
	}

	void GL::BindBuffer(GLenum target, GLuint buffer)
	{
		glBindBuffer(target, buffer);
		GL_DIAGNOSTIC_CHECK();
	}

	void GL::BufferData(GLenum target, GLsizeiptr size, const GLvoid * data, GLenum usage)
	{
		glBufferData(target, size, data, usage);
		GL_DIAGNOSTIC_CHECK();
	}

	void GL::VertexAttributePointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer)
	{
		glVertexAttribPointer(index, size, type, normalized, stride, pointer);
		GL_DIAGNOSTIC_CHECK();
	}

	void GL::Enable(GLenum cap)
	{
		glEnable(cap);
		GL_DIAGNOSTIC_CHECK();
	}

	void GL::Disable(GLenum cap)
	{
		glDisable(cap);
		GL_DIAGNOSTIC_CHECK();
	}

	void GL::BlendFunction(GLenum sfactor, GLenum dfactor)
	{
		glBlendFunc(sfactor, dfactor);
		GL_DIAGNOSTIC_CHECK();
	}

	void GL::ActiveTexture(GLenum texture)
	{
		glActiveTexture(texture);
		GL_DIAGNOSTIC_CHECK();
	}

	void GL::EnableVertexAttributeArray(GLuint index)
	{
		glEnableVertexAttribArray(index);
		GL_DIAGNOSTIC_CHECK();
	}

	void GL::DisableVertexAttribArray(GLuint index)
	{
		glDisableVertexAttribArray(index);
		GL_DIAGNOSTIC_CHECK();
	}

	void GL::DrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid * indices)
	{
		glDrawElements(mode, count, type, indices);
		GL_DIAGNOSTIC_CHECK();
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
		GL_DIAGNOSTIC_CHECK();
	}

	void GL::CompileShader(GLuint shader)
	{
		glCompileShader(shader);
		GL_DIAGNOSTIC_CHECK();
	}

	void GL::GetShaderParameter(GLuint shader, GLenum pname, GLint * params)
	{
		glGetShaderiv(shader, pname, params);
		GL_DIAGNOSTIC_CHECK();
	}

	void GL::GetShaderInfoLog(GLuint shader, GLsizei maxLength, GLsizei * length, GLchar * infoLog)
	{
		glGetShaderInfoLog(shader, maxLength, length, infoLog);
		GL_DIAGNOSTIC_CHECK();
	}

	void GL::DeleteShader(GLuint shader)
	{
		glDeleteShader(shader);
		GL_DIAGNOSTIC_CHECK();
	}

	void GL::LinkProgram(GLuint program)
	{
		glLinkProgram(program);
		GL_DIAGNOSTIC_CHECK();
	}

	void GL::GetProgramParameter(GLuint program, GLenum pname, GLint * params)
	{
		glGetProgramiv(program, pname, params);
		GL_DIAGNOSTIC_CHECK();
	}

	void GL::GetProgramInfoLog(GLuint program, GLsizei maxLength, GLsizei * length, GLchar * infoLog)
	{
		glGetProgramInfoLog(program, maxLength, length, infoLog);
		GL_DIAGNOSTIC_CHECK();
	}

	void GL::DeleteProgram(GLuint program)
	{
		glDeleteProgram(program);
		GL_DIAGNOSTIC_CHECK();
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
		GL_DIAGNOSTIC_CHECK();
	}

	void GL::AttachShader(GLuint program, GLuint shader)
	{
		glAttachShader(program, shader);
		GL_DIAGNOSTIC_CHECK();
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
		GL_DIAGNOSTIC_CHECK();
	}

	void GL::Uniform(GLint location, GLint v0)
	{
		glUniform1i(location, v0);
		GL_DIAGNOSTIC_CHECK();
	}
}

void GL_Verify(void)
{
	GLenum err;

	while ((err = glGetError()) != GL_NO_ERROR)
	{
		std::string message = StringHelper::GetFormattedString("OpenGL Error: Error Code %d", 1024, err);
		throw Exception(message);
	}
}

GLuint GL_Verify(GLuint returnValue)
{
	if (returnValue <= 0)
		GL_Verify();

	return returnValue;
}
