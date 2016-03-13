#pragma once

#include <GL\gl.h>

#include <stdarg.h>
#include <string>

class OpenGLAdapter
{
public:
	// Constructor
	OpenGLAdapter();

	// Destructor
	virtual ~OpenGLAdapter();

	// set matrix mode
	void SetMatrixMode(GLenum mode);

	// safe load identity matrix
	void SafeLoadIdentityMatrix();

	// load identity matrix
	void LoadIdentityMatrix();

	// safe set clear color
	void SafeSetClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);

	// set clear color
	void SetClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);

	// assert that no error happened
	void AssertNoError();

	// clear screen
	void ClearScreen();

	// begin primitive
	void BeginPrimitive(GLenum mode);

	// set vertex 2D
	void SetVertex2D(GLfloat x, GLfloat y);

	// end primitive
	void EndPrimitive();
};
