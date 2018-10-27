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
		Vector2f getResolution() const;

		// set the resolution
		void setResolution(const Vector2f& resolution);

		// clear the window
		void clear();

		// swap the video buffers
		void swap();

	protected:
		// apply the default resolution to the window
		Vector2f getDefaultResolution();

		// create the sdl window
		void createSdlWindow(Vector2f resolution);

	private:
		// the sdl window
		SDL_Window* m_sdlWindow;

		// the opengl context
		SDL_GLContext m_openGlContext;
	};
}