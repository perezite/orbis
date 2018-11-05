#include "Shape.h"

namespace orb
{
	Shape::Shape(unsigned int numVertices)
		: m_shapeRenderer(numVertices)
	{
		addComponent(&m_shapeRenderer);
	}
}