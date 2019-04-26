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
		const Vector2u getResolution() const;

		// set the resolution
		void setResolution(const Vector2u& resolution);

		// clear the window
		void clear();

		// display by swapping the back and front buffer 
		void display();

	protected:
		// apply the default resolution to the window
		const Vector2u getDefaultResolution() const;

		// create the sdl window
		void createSdlWindow(const Vector2u& resolution);

	private:
		// the sdl window
		SDL_Window* m_sdlWindow;

		// the opengl context
		SDL_GLContext m_openGlContext;
	};
}