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

namespace Libraries
{
	// wrapper class for OpenGL calls
	class GL
	{
	public:
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