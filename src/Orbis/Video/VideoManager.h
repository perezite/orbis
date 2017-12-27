#pragma once

#include "RenderDevice.h"

#include "../Libraries/SDL.h"
#include "../Components/Renderer.h"
using namespace Components;

#include "../../Base/Math/Vector2D.h"
using namespace Math;

namespace Video
{
	class VideoManager
	{
	public:
		// get instance
		static VideoManager* GetInstance();

		// initialize
		void Initialize();

		// destructor
		virtual ~VideoManager();

		// get the resolution
		Vector2D GetResolution() { return m_windowResolution; }

		// get the render device
		RenderDevice* GetRenderDevice() { return &m_renderDevice; }

		// clear the screen
		void ClearScreen();

		// swap the video buffers
		void SwapBuffers();

	protected:
		// singleton constructor
		VideoManager();

		// get the default window resolution
		Vector2D GetDefaultWindowResolution();
	private:
		// the sdl window
		SDL_Window* m_sdlWindow;

		// the opengl context
		SDL_GLContext m_openGlContext;

		// the attached render device
		RenderDevice m_renderDevice;

		// the window resolution
		Vector2D m_windowResolution;

		// the default window resolution
		static const Vector2D m_DefaultWindowResolution;

		// is the manager initialized
		bool m_IsInitialized;
	};
}

