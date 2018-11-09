#pragma once

#include <string>
#include "Mesh.h"
#include "Transform.h"
#include "Renderer.h"

namespace orb
{
	class Window
	{
	public:
		Window(unsigned int width, unsigned int height, std::string title) : m_title(title) {}

		bool isOpen() const { return true; }

		void clear() { }

		void draw(Mesh& mesh, const Transform& transform);

		void display() {
			m_renderer.display();
		}

	private:
		std::string m_title;

		Renderer m_renderer;
	};
}
