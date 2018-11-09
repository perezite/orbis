#include "Window.h"

namespace orb
{
	void Window::draw(Mesh& mesh, const Transform& transform) 
	{
		m_renderer.draw(mesh, transform);
	}
}