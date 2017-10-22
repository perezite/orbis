#pragma once

// set this define to enable exceptions for non performance critical GL calls
#define GL_NORMAL_EXCEPTIONS

// set this define to enable exceptions for all GL calls, even performance critical ones. Only this only for diagnosing errors!
#ifdef _DEBUG
	#define GL_DIAGNOSTIC_EXCEPTIONS
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
	};
}