#pragma once

#include "RenderDevice_v2.h"

#include "../Libraries/SDL.h"

#include "../../Base/Math/Vector2D.h"
using namespace Math;

namespace Video 
{
	class VideoManager_v2
	{
	public:
		// get instance
		static VideoManager_v2* GetInstance();

		// initialize
		void Initialize();

		// destructor
		virtual ~VideoManager_v2();

		// get the resolution
		Vector2D GetResolution() { return m_windowResolution; }

		// get the render device
		RenderDevice_v2* GetRenderDevice() const { return m_renderDevice; }

		// clear the screen
		void ClearScreen();

		// swap the video buffers
		void SwapBuffers();

	protected:
		// singleton constructor
		VideoManager_v2();

		// get the default window resolution
		Vector2D GetDefaultWindowResolution();

	private:
		// the sdl window
		SDL_Window* m_sdlWindow;

		// the opengl context
		SDL_GLContext m_openGlContext;

		// the attached render device
		RenderDevice_v2* m_renderDevice;

		// the window resolution
		Vector2D m_windowResolution;

		// the default window resolution
		static const Vector2D m_DefaultWindowResolution;

		// is the manager initialized
		bool m_IsInitialized;
	};
}

