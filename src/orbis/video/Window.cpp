#include "Window.h"

namespace orb
{
	Window::Window(unsigned int width, unsigned int height, std::string title) 
		: m_title(title) 
	{
		initSDL();
	};

	void Window::draw(Mesh& mesh, const Transform& transform) 
	{
		m_renderer.draw(mesh, transform);
	}

	void Window::display()
	{
		m_renderer.print();
	}

	void Window::initSDL()
	{
		#ifdef WIN32
				SDL_Init(SDL_INIT_VIDEO);
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
				SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
				SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
				m_sdlWindow = SDL_CreateWindow("Sandbox", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 400, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
				m_glContext = SDL_GL_CreateContext(m_sdlWindow);
				GLenum glewError = glewInit();
		#elif defined(__ANDROID__)
				SDL_Init(SDL_INIT_VIDEO);
				SDL_DisplayMode mode;
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
				SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
				SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
				SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
				SDL_GetDisplayMode(0, 0, &mode);
				m_sdlWindow = SDL_CreateWindow("Sandbox", 0, 0, mode.w, mode.h, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_SHOWN);
				m_glContext = SDL_GL_CreateContext(m_sdlWindow);
		#endif	
	}
}