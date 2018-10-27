#pragma once

#include "../../Base/Base.h"
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
		Vector2D getResolution() const;

		// set the resolution
		void setResolution(const Vector2D& resolution);

		// clear the window
		void clear();

		// swap the video buffers
		void swap();

	protected:
		// apply the default resolution to the window
		Vector2D getDefaultResolution();

		// create the sdl window
		void createSdlWindow(Vector2D resolution);

	private:
		// the sdl window
		SDL_Window* m_sdlWindow;

		// the opengl context
		SDL_GLContext m_openGlContext;
	};
}