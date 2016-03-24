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
		void Update();

	protected:
		// Initialize SDL
		void InitializeSDLVideo(int windowWidth, int windowHeight);

		// Initialize OpenGL
		void InitializeOpenGL();

		// Render
		// TODO: move to renderer
		void Render();

	private:
		// OpenGL adapter
		OpenGLAdapter *m_openGLAdapter;
	};
}