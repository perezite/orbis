#include "Window.h"

#include "../Libraries/GL.h"
#include "../Engine/Settings.h"

namespace orb
{
	Window::Window()
	{
		SDL_Init(SDL_INIT_VIDEO);
		IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
				
		#ifdef WIN32	
			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
			SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
			createSdlWindow(getDefaultResolution());
			glewInit();
		#endif	
		#ifdef __ANDROID__
			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
			SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
			SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
			createSdlWindow(getDefaultResolution());
		#endif

		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
	}

	Window::~Window()
	{
		SDL_DestroyWindow(m_sdlWindow);
	}

	const Vector2u Window::getResolution() const
	{
		int x, y;
		SDL_GL_GetDrawableSize(m_sdlWindow, &x, &y);
		return Vector2u((unsigned int)x, (unsigned int)y);
	}

	void Window::setResolution(const Vector2u& resolution)
	{
		Exception::assert(!EnvironmentUtil::isMobile(), "The resolution cannot be changed on mobile platforms");

		SDL_DestroyWindow(m_sdlWindow);
		createSdlWindow(resolution);
	}

	void Window::clear()
	{
		glClearColor(0.95f, 0.95f, 0.95f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	
	void Window::display()
	{
		SDL_GL_SwapWindow(m_sdlWindow);
	}

	const Vector2u Window::getDefaultResolution() const
	{
		if (EnvironmentUtil::isMobile()) {
			SDL_DisplayMode mode;
			SDL_GetDisplayMode(0, 0, &mode);
			return Vector2u((unsigned int)mode.w, (unsigned int)mode.h);
		}

		return ORBIS_DESKTOP_DEFAULT_RESOLUTION;
	}

	void Window::createSdlWindow(const Vector2u& resolution)
	{
		#if defined(WIN32)
			m_sdlWindow = SDL_CreateWindow("Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, (int)resolution.x, (int)resolution.y, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		#elif defined(__ANDROID__)
			m_sdlWindow = SDL_CreateWindow("Example", 0, 0, (int)resolution.x, (int)resolution.y, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_SHOWN);
		#endif

		m_openGlContext = SDL_GL_CreateContext(m_sdlWindow);
		SDL_GL_MakeCurrent(m_sdlWindow, m_openGlContext);
		glViewport(0, 0, (int)resolution.x, (int)resolution.y);
	}
}