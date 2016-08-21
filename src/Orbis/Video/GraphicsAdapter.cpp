#include <GL\glew.h>
#include <GL\glu.h>
#include <gl\gl.h>

#include "GraphicsAdapter.h"

#include "..\..\Base\System\Exception.h"
#include "..\..\Base\System\StringHelper.h"
using namespace System;

#include "..\..\Base\Math\MathHelper.h"
using namespace Math;

#include <iostream>

namespace Video
{
	SDL_Window* GraphicsAdapter::m_SDLWindow = NULL;

	SDL_GLContext GraphicsAdapter::m_OpenGLContext;

	void GraphicsAdapter::SetMatrixMode(MatrixMode matrixMode)
	{
		glMatrixMode((GLenum)matrixMode);
	}

	void GraphicsAdapter::SafeLoadIdentityMatrix()
	{
		LoadIdentityMatrix();
		AssertNoError();
	}

	void GraphicsAdapter::LoadIdentityMatrix()
	{
		glLoadIdentity();
	}

	void GraphicsAdapter::ApplyGlobalTranslation(Vector2D translation)
	{
		glTranslatef(translation.GetX(), translation.GetY(), 0.0f);
	}

	void GraphicsAdapter::ApplyGlobalScale(Vector2D scale)
	{
		glScalef(scale.GetX(), scale.GetY(), 0.0f);
	}

	void GraphicsAdapter::ApplyGlobalRotation(float rotation)
	{
		glRotatef(MathHelper::RadianToDegrees(rotation), 0.0f, 0.0f, 1.0f);
	}

	void GraphicsAdapter::SafeSetClearColor(Color color)
	{
		SetClearColor(color);
		AssertNoError();
	}

	void GraphicsAdapter::SetClearColor(Color color)
	{
		glClearColor((GLclampf)color.GetRed(), (GLclampf)color.GetGreen(), (GLclampf)color.GetBlue(), (GLclampf)color.GetAlpha());
	}

	void GraphicsAdapter::ClearScreen()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void GraphicsAdapter::BeginPrimitive(RenderMode renderMode)
	{
		glBegin((GLenum)renderMode);
	}

	void GraphicsAdapter::SetVertex2D(Vector2D position)
	{
		glVertex2d((GLfloat)position.GetX(), (GLfloat)position.GetY());
	}

	void GraphicsAdapter::EndPrimitive()
	{
		glEnd();
	}

	void GraphicsAdapter::InitializeGraphics(int windowWidth, int windowHeight)
	{
		InitializeSDLVideoSubsystem();
		CreateSDLWindow(windowWidth, windowHeight);
		CreateOpenGLContext();
		SetOpenGLSwapInterval(1);
		// std::cout << StringHelper::GetFormattedString("OpenGL Renderer: %s", glGetString(GL_RENDERER)) << std::endl;
		// std::cout << StringHelper::GetFormattedString("OpenGL Vendor: %s", glGetString(GL_VENDOR)) << std::endl;
	}

	void GraphicsAdapter::QuitGraphics()
	{
		SDL_QuitSubSystem(SDL_INIT_VIDEO);
		DestroySDLWindow();

	}

	void GraphicsAdapter::SwapBuffers()
	{
		SDL_GL_SwapWindow(m_SDLWindow);
	}

	void GraphicsAdapter::AssertNoError()
	{
		GLenum error = glGetError();

		if (error != GL_NO_ERROR)
		{
			std::string formattedError = StringHelper::GetFormattedString("%s", gluErrorString(error));
			throw Exception("OpenGL error: " + formattedError);
		}
	}

	void GraphicsAdapter::InitializeSDLVideoSubsystem()
	{
		int result = SDL_Init(SDL_INIT_VIDEO);

		if (result != 0)
		{
			throw Exception("SDL_Init failed");
		}
	}

	void GraphicsAdapter::CreateSDLWindow(int windowWidth, int windowHeight)
	{
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, OpenGLContextMajorVersion);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, OpenGLContextMinorVersion);
		// SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

		m_SDLWindow = SDL_CreateWindow("Orbis", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

		if (m_SDLWindow == NULL)
		{
			throw Exception("SDL_CreateWindow failed");
		}
	}

	void GraphicsAdapter::DestroySDLWindow()
	{
		SDL_DestroyWindow(m_SDLWindow);
	}

	void GraphicsAdapter::CreateOpenGLContext()
	{
		m_OpenGLContext = SDL_GL_CreateContext(m_SDLWindow);

		if (m_OpenGLContext == NULL)
		{
			throw Exception("SDL_GL_CreateContext failed");
		}
	}

	void GraphicsAdapter::SetOpenGLSwapInterval(int interval)
	{
		int result = SDL_GL_SetSwapInterval(1);

		if (result != 0)
		{
			// TODO: use a logger class
			std::cout << "Warning: GL_SetSwapInterval failed" << std::endl;
		}
	}
}