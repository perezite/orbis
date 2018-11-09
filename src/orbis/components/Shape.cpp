#include "Shape.h"

namespace orb
{
	void Shape::draw(orb::Window& window, const orb::Transform& transform)
	{
		orb::Transform combinedTransform = transform * getTransform();
		window.draw(m_mesh, transform);
	}
}
