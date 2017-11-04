#pragma once

// only set this define for diagnosing bad gl calls, do not use in release mode
#define GL_DIAGNOSTICS 

#ifdef __ANDROID__
	#include <GLES2/gl2.h>	
	#include <GLES2/gl2ext.h>
#endif 
#ifdef WIN32
	#include <gl/glew.h>
	#include <SDL2/SDL_opengl.h>
	#include <gl/glu.h>
#endif

void GL_Verify();

GLuint GL_Verify(GLuint returnValue);

GLint GL_Verify(GLint returnValue);

#define GL_VERIFY(call) \
	call,				\
	GL_Verify()			

#if defined(WIN32)
	#define GLEW_ORIGINAL(call) GLEW_GET_FUN(__glew ## call)
#else
	#define GLEW_ORIGINAL(call) gl ## call
#endif

#define glGenTextures(n, textures) GL_VERIFY(glGenTextures(n, textures))

#define glBindTexture(target, texture) GL_VERIFY(glBindTexture(target, texture))

#define glTexImage2D(target, level, internalFormat, width, height, border, format, type, data) \
	GL_VERIFY(glTexImage2D(target, level, internalFormat, width, height, border, format, type, data))

#define glTexParameteri(texture, pname, param) GL_VERIFY(glTexParameteri(texture, pname, param))

#undef glGenBuffers
#define glGenBuffers(n, buffers) GL_VERIFY(GLEW_ORIGINAL(GenBuffers)(n, buffers))

#undef glBindBuffer
#define glBindBuffer(target, buffer) GL_VERIFY(GLEW_ORIGINAL(BindBuffer)(target, buffer))

#undef glBufferData
#define glBufferData(target, size, data, usage) GL_VERIFY(GLEW_ORIGINAL(BufferData)(target, size, data, usage))

#define glEnable(cap) GL_VERIFY(glEnable(cap))

#define glBlendFunc(sfactor, dfactor) GL_VERIFY(glBlendFunc(sfactor, dfactor))

#undef glEnableVertexAttribArray
#define glEnableVertexAttribArray(index) GL_VERIFY(GLEW_ORIGINAL(EnableVertexAttribArray)(index))

#undef glVertexAttribPointer
#define glVertexAttribPointer(index, size, type, normalized, stride, pointer) GL_VERIFY(GLEW_ORIGINAL(VertexAttribPointer)(index, size, type, normalized, stride, pointer))

#define glDrawElements(mode, count, type, indices) GL_VERIFY(glDrawElements(mode, count, type, indices))

#undef glDisableVertexAttribArray
#define glDisableVertexAttribArray(index) GL_VERIFY(GLEW_ORIGINAL(DisableVertexAttribArray)(index))

#define glDisable(cap) GL_VERIFY(glDisable(cap))

#undef glCreateShader
#define glCreateShader(type) GL_Verify(GLEW_ORIGINAL(CreateShader)(type))

#undef glShaderSource
#define glShaderSource(shader, count, string, length) GL_VERIFY(GLEW_ORIGINAL(ShaderSource)(shader, count, string, length))

#undef glCompileShader
#define glCompileShader(shader) GL_VERIFY(GLEW_ORIGINAL(CompileShader)(shader))

#undef glGetShaderiv
#define glGetShaderiv(shader, pname, params) GL_VERIFY(GLEW_ORIGINAL(GetShaderiv)(shader, pname, params))

#undef glGetShaderInfoLog
#define glGetShaderInfoLog(shader, maxLength, length, infoLog) GL_VERIFY(GLEW_ORIGINAL(GetShaderInfoLog)(shader, maxLength, length, infoLog))

#undef glDeleteShader
#define glDeleteShader(shader) GL_VERIFY(GLEW_ORIGINAL(DeleteShader)(shader))

#undef glLinkProgram
#define glLinkProgram(program) GL_VERIFY(GLEW_ORIGINAL(LinkProgram)(program))

#undef glGetProgramiv
#define glGetProgramiv(program, pname, params) GL_VERIFY(GLEW_ORIGINAL(GetProgramiv)(program, pname, params))

#undef glGetProgramInfoLog
#define glGetProgramInfoLog(program, maxLength, length, infoLog) GL_VERIFY(GLEW_ORIGINAL(GetProgramInfoLog)(program, maxLength, length, infoLog))

#undef glDeleteProgram
#define glDeleteProgram(program) GL_VERIFY(GLEW_ORIGINAL(DeleteProgram)(program))

#undef glCreateProgram
#define glCreateProgram() GL_Verify(GLEW_ORIGINAL(CreateProgram)())

#undef glAttachShader
#define glAttachShader(program, shader) GL_VERIFY(GLEW_ORIGINAL(AttachShader)(program, shader))

#undef glGetAttribLocation
#define glGetAttribLocation(program, name) GL_Verify(GLEW_ORIGINAL(GetAttribLocation)(program, name))

#undef glGetUniformLocation
#define glGetUniformLocation(program, name) GL_Verify(GLEW_ORIGINAL(GetUniformLocation)(program, name))

#undef glUniformMatrix4fv
#define glUniformMatrix4fv(location, count, transpose, value) GL_VERIFY(GLEW_ORIGINAL(UniformMatrix4fv)(location, count, transpose, value))

#undef glUniform1i
#define glUniform1i(location, v0) GL_VERIFY(GLEW_ORIGINAL(Uniform1i)(location, v0))

#undef glUseProgram
#define glUseProgram(program) GL_VERIFY(GLEW_ORIGINAL(UseProgram)(program))

namespace Libraries
{
	// wrapper class for OpenGL calls
	class GL
	{
	public:
		static void Temp();

		// clear color
		static void ClearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

		// clear the screen
		static void Clear(GLbitfield mask);

		// generate textures
		static void GenerateTextures(GLsizei n, GLuint * textures);

		// generate buffers
		static void GenerateBuffers(GLsizei n, GLuint * buffers);

		// bind a texture
		static void BindTexture(GLenum target, GLuint texture);

		// set a 2D texture image
		static void TextureImage2D(GLenum target, GLint level, GLint internalFormat,
			GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* data);
			
		// set a texture parameter
		static void TextureParameter(GLenum target, GLenum pname, GLint param);
			
		// bind buffer
		static void BindBuffer(GLenum target, GLuint buffer);

		// set buffer data
		static void BufferData(GLenum target, GLsizeiptr size, const GLvoid * data, GLenum usage);

		// set a vertex shader attribute pointer
		static void VertexAttributePointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer);

		// enable a capability
		static void Enable(GLenum cap);

		// disable a capability
		static void Disable(GLenum cap);

		// set the blend function
		static void BlendFunction(GLenum sfactor, GLenum dfactor);

		// set the active texture unit
		static void ActiveTexture(GLenum texture);

		// enable a vertex shader attribute array
		static void EnableVertexAttributeArray(GLuint index);

		// disable a vertex shader attribute array
		static void DisableVertexAttribArray(GLuint index);

		// draw elements
		static void DrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid * indices);

		// create a shader
		static GLuint CreateShader(GLenum shaderType);

		// set the shader source code
		static void ShaderSource(GLuint shader, GLsizei count, const GLchar** string, const GLint *length);

		// compile a shader
		static void CompileShader(GLuint shader);

		// get a parameter from a shader object
		static void GetShaderParameter(GLuint shader, GLenum pname, GLint *params);

		// get the shader info log
		static void GetShaderInfoLog(GLuint shader, GLsizei maxLength, GLsizei *length, GLchar *infoLog);

		// delete a shader
		static void DeleteShader(GLuint shader);

		// link a program
		static void LinkProgram(GLuint program);

		// get program parameter
		static void GetProgramParameter(GLuint program, GLenum pname, GLint *params);

		// get the program info log
		static void GetProgramInfoLog(GLuint program, GLsizei maxLength, GLsizei *length, GLchar *infoLog);

		// delete a program
		static void DeleteProgram(GLuint program);

		// create a program
		static GLuint CreateProgram();

		// use a program
		static void UseProgram(GLuint program);

		// attach a shader to a program
		static void AttachShader(GLuint program, GLuint shader);

		// get the location of a shader attribute
		static GLint GetAttributeLocation(GLuint program, const GLchar *name);

		// get the location of a shader uniform
		static GLint GetUniformLocation(GLuint program, const GLchar *name);

		// set a matrix4 uniform
		static void UniformMatrix4(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);

		// set a scalar uniform
		static void Uniform(GLint location, GLint v0);
	};
}