#pragma once

#define NO_SDL_GLEXT
#include <SDL_opengl.h>
#include <SDL.h>

namespace Base
{
	class SDLAdapter
	{
	public:
		// Quit SDL
		static void QuitSDL();

		// Create window
		static void CreateSDLWindow(int windowWidth, int windowHeight);

		// Destroy window
		static void DestroySDLWindow();

		// Initialize video
		static void InitializeVideoSubsystem();

		// Quit video
		static void QuitVideoSubsystem();

		// Create openGL context
		static void CreateOpenGLContext();

		// Set OpenGL swap interval
		static void SetOpenGLSwapInterval(int interval);

		// Swap OpenGL buffers
		static void SwapOpenGLBuffers();

		// Check if there is at least one pending event
		static bool HasPendingEvents();

		// Poll event
		static SDL_Event PollEvent();
	private:
		// SDL window
		static SDL_Window *m_SDLWindow;

		// SDL OpenGL context
		static SDL_GLContext m_OpenGLContext;

		static const int OpenGLContextMajorVersion = 2;

		static const int OpenGLContextMinorVersion = 1;
	};
}