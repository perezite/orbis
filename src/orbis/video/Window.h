#pragma once

#include "Mesh.h"
#include "Transform.h"
#include "Renderer.h"
#include "OpenGL.h"
#include <SDL2/SDL.h>
#include <string>

namespace orb
{
	class Window
	{
	public:
		Window(unsigned int width, unsigned int height, std::string title);

		bool isOpen() const { return true; }

		void clear() { }

		void draw(Mesh& mesh, const Transform& transform);

		void display();

	protected:
		void initSDL();

	private:
		std::string m_title;

		SDL_Window* m_sdlWindow;

		SDL_GLContext m_glContext;

		Renderer m_renderer;
	};
}
