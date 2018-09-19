#pragma once

#include "../../Base/Math/Vector2D.h"
using namespace base;

#include "../Libraries/SDL.h"

namespace orb
{
	class Window
	{
	public:
		// ctor
		Window();

		// dtor
		virtual ~Window();

		// get the resolution
		Vector2D getResolution() { return m_resolution; }

		// change the window resultion
		void setResolution(Vector2D resolution);

		// clear
		void clear();

		// swap the video buffers
		void swapBuffers();

	protected:
		// get the default window resolution
		Vector2D getDefaultResolution();

		// create the sdl window
		void createSdlWindow();

	private:
		// the sdl window
		SDL_Window* m_sdlWindow;

		// the opengl context
		SDL_GLContext m_openGlContext;

		// the window resolution
		Vector2D m_resolution;

		// the default window resolution
		static const Vector2D DESKTOP_DEFAULT_RESOLUTION;
	};
}