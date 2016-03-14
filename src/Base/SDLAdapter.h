#pragma once

#define NO_SDL_GLEXT
#include <SDL_opengl.h>
#include <SDL.h>

namespace Base
{
	class SDLAdapter
	{
	public:
		// Constructor
		SDLAdapter();

		// Destructor
		virtual ~SDLAdapter();

		// Initialize video
		void InitializeVideoSubsystem();

		// Create window
		void CreateSDLWindow(int windowWidth, int windowHeight);

		// Create openGL context
		void CreateOpenGLContext();

		// Set OpenGL swap interval
		void SetOpenGLSwapInterval(int interval);

		// Swap OpenGL buffers
		void SwapOpenGLBuffers();

		// Check if there is at least one pending event
		bool HasPendingEvents();

		// Poll event
		SDL_Event PollEvent();

		// Destroy window
		void DestroyWindow();

	public:
		// SDL window
		SDL_Window* m_SDLWindow;

		// SDL OpenGL context
		SDL_GLContext m_OpenGLContext;

		const int OpenGLContextMajorVersion = 2;

		const int OpenGLContextMinorVersion = 1;
		//SDL_GL_CONTEXT_MAJOR_VERSION
	};
}