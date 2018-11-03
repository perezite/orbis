#include "Shape.h"

namespace orb
{
	Shape::Shape(PrimitiveType primitiveType, unsigned int size)
		: m_shapeRenderer(primitiveType, size)
	{
		addComponent(&m_shapeRenderer);
	}
}