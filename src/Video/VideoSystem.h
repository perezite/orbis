#pragma once

#include "..\Base\SDLAdapter.h"
#include "..\Base\OpenGLAdapter.h"

using namespace Base;

namespace Video
{
	class VideoSystem
	{
	public:
		// Constructor
		VideoSystem(int windowWidth, int windowHeight);

		// Destructor
		virtual ~VideoSystem();

		// Run 
		// TODO: move to input system
		void Run();

	protected:
		// Initialize SDL
		void InitializeSDL(int windowWidth, int windowHeight);

		// Create SDL video subsystem
		void initializeSDLVideoSubsystem();

		// Create SDL OpenGL context
		void createSDLOpenGLContext();

		// Set SDL OpenGL Swap interval
		void setSDLOpenGLSwapInterval();

		// Initialize OpenGL
		void InitializeOpenGL();

		// Render
		// TODO: move to renderer
		void Render();

	private:
		// OpenGL adapter
		OpenGLAdapter *m_openGLAdapter;

		// SDL adapter
		SDLAdapter *m_SDLAdapter;


		// SDL window
		//SDL_Window* m_SDLWindow = NULL;

		// SDL OpenGL contex
		// SDL_GLContext m_OpenGLContext;
	};
}