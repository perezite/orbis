#include <GL\glew.h>
#include <GL\glu.h>
#include <gl\gl.h>

#include "OpenGLAdapter.h"

#include "StringHelper.h"
#include "Exception.h"

OpenGLAdapter::OpenGLAdapter()
{
}

OpenGLAdapter::~OpenGLAdapter()
{
}

void OpenGLAdapter::SetMatrixMode(GLenum mode)
{
	glMatrixMode(mode);
}

void OpenGLAdapter::SafeLoadIdentityMatrix()
{
	LoadIdentityMatrix();
	AssertNoError();
}

void OpenGLAdapter::LoadIdentityMatrix()
{
	glLoadIdentity();
}

void OpenGLAdapter::SafeSetClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
	SetClearColor(red, green, blue, alpha);
	AssertNoError();
}

void OpenGLAdapter::SetClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void OpenGLAdapter::AssertNoError()
{
	GLenum error = glGetError();

	if (error != GL_NO_ERROR)
	{
		std::string formattedError = StringHelper::GetFormattedString("%s", gluErrorString(error));
		throw Exception("OpenGL error: " + formattedError);
	}
}

void OpenGLAdapter::ClearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLAdapter::BeginPrimitive(GLenum mode)
{
	glBegin(mode);
}

void OpenGLAdapter::SetVertex2D(GLfloat x, GLfloat y)
{
	glVertex2d(x, y);
}

void OpenGLAdapter::EndPrimitive()
{
	glEnd();
}
