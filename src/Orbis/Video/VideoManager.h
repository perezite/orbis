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
		void Initialize(bool useDefaultResolution = true);

		// destructor
		virtual ~VideoManager();

		// get the resolution
		Vector2D GetResolution() { return m_windowResolution; }

		// change the window resultion
		void SetResolution(Vector2D resolution);

		// get the render device
		RenderDevice* GetRenderDevice() { return &m_renderDevice; }

		// clear the screen
		void ClearScreen();

		// swap the video buffers
		void SwapBuffers();

		// shutdown video
		void Shutdown();

	protected:
		// singleton constructor
		VideoManager();

		// get the default window resolution
		Vector2D GetDefaultWindowResolution();

		// initialize SDL video subsystem
		void InitSDL();
	private:
		// the sdl window
		SDL_Window* m_sdlWindow;

		// the opengl context
		SDL_GLContext m_openGlContext;

		// the attached render device
		RenderDevice m_renderDevice;

		// the window resolution
		Vector2D m_windowResolution;

		// is the manager initialized
		bool m_isInitialized;

		// the default window resolution
		static const Vector2D DESKTOP_DEFAULT_RESOLUTION;
	};
}

