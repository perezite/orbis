#pragma once

#include "GL.h"
#include <SDL2/SDL.h>

namespace sb
{
	namespace renderer2
	{
		class Window
		{
		public:
			bool hasQuitEvent() { return m_hasQuitEvent; }

			void init(int width = 400, int height = 400);

			void flip();

			void update();

			void destroy();

		private:
			bool m_hasQuitEvent;

			SDL_Window* m_sdlWindow;

			SDL_GLContext m_glContext;
		};
	}
}