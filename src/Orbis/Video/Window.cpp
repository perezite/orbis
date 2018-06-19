#include "Window.h"

#include "../Libraries/GL.h"

#include "../../Base/Math/Vector2D.h"
#include "../../Base/System/EnvironmentHelper.h"
using namespace Math;
using namespace System;

namespace Video
{
	const Vector2D Window::DESKTOP_DEFAULT_RESOLUTION(400, 711);

	Window::Window()
	{
		SDL_Init(SDL_INIT_VIDEO);
		m_resolution = getDefaultResolution();

		#ifdef WIN32	
			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
			SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
			createSdlWindow();
			m_openGlContext = SDL_GL_CreateContext(m_sdlWindow);
			glewInit();
		#endif	
		#ifdef __ANDROID__
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
			SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
			SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
			createSdlWindow();
			m_openGlContext = SDL_GL_CreateContext(m_sdlWindow);
		#endif

		glViewport(0, 0, (int)m_resolution.x, (int)m_resolution.y);
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
	}

	Window::~Window()
	{
		SDL_DestroyWindow(m_sdlWindow);
	}

	void Window::setResolution(Vector2D resolution)
	{
		if (EnvironmentHelper::IsMobile())
			return;

		SDL_DestroyWindow(m_sdlWindow);
		m_resolution = resolution;
		createSdlWindow();

		SDL_GL_MakeCurrent(m_sdlWindow, m_openGlContext);
		glViewport(0, 0, (int)m_resolution.x, (int)m_resolution.y);
	}

	void Window::clear()
	{
		glClearColor(0.95f, 0.95f, 0.95f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Window::swapBuffers()
	{
		SDL_GL_SwapWindow(m_sdlWindow);
	}

	Vector2D Window::getDefaultResolution()
	{
		if (EnvironmentHelper::IsMobile())
		{
			SDL_DisplayMode mode;
			SDL_GetDisplayMode(0, 0, &mode);
			return Vector2D((float)mode.w, (float)mode.h);
		}

		else 
			return DESKTOP_DEFAULT_RESOLUTION;
	}

	void Window::createSdlWindow()
	{
		#ifdef WIN32
			m_sdlWindow = SDL_CreateWindow("Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, (int)m_resolution.x, (int)m_resolution.y, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		#endif
		#ifdef __ANDROID__
			m_sdlWindow = SDL_CreateWindow("Example", 0, 0, (int)m_resolution.x, (int)m_resolution.y, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_SHOWN);
		#endif
	}
}