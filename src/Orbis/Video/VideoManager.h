#pragma once

#include "RenderDevice.h"

#include "../../Base/Math/Vector2D.h"
using namespace Math;

#include "SDL2/SDL.h"

namespace Video
{
	class VideoManager
	{
	public:
		// get instance
		static VideoManager* GetInstance();

		// destructor
		virtual ~VideoManager();

		// get the render device
		RenderDevice* GetRenderDevice();

		// clear the screen
		void ClearScreen();

		// swap the video buffers
		void SwapBuffers();

	protected:
		// singleton constructor
		VideoManager();

		// get the default window resolution
		Vector2D GetDefaultWindowResolution();

		// initialize the video
		void InitializeVideo();

	private:
		// the sdl window
		SDL_Window* m_sdlWindow;

		// the opengl context
		SDL_GLContext m_openGlContext;

		// the attached render device
		RenderDevice* m_renderer;

		// the window resolution
		Vector2D m_windowResolution;

		// the default window resolution
		static const Vector2D m_DefaultWindowResolution;
	};
}