#pragma once

#include "..\Base\\SDLAdapter.h"

#include <GL\gl.h>

namespace Base
{
	class OpenGLAdapter
	{
	public:
		// set matrix mode
		static void SetMatrixMode(GLenum mode);

		// safe load identity matrix
		static void SafeLoadIdentityMatrix();

		// load identity matrix
		static void LoadIdentityMatrix();

		// safe set clear color
		static void SafeSetClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);

		// set clear color
		static void SetClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);

		// assert that no error happened
		static void AssertNoError();

		// clear screen
		static void ClearScreen();

		// begin primitive
		static void BeginPrimitive(GLenum mode);

		// set vertex 2D
		static void SetVertex2D(GLfloat x, GLfloat y);

		// end primitive
		static void EndPrimitive();
	};
}