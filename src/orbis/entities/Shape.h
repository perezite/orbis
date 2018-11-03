#pragma once

#include "Entity.h"
#include "../video/Mesh.h"
#include "../Components/ShapeRenderer.h"

#include <iostream>

namespace orb 
{
	// an entity with a shape that can be drawn onto the screen
	class Shape : public Entity
	{
	public:
		Shape(PrimitiveType primitiveType, unsigned int size);

		virtual ~Shape() { };

		Vertex& operator[](std::size_t index) { return m_shapeRenderer[index]; }

	private: 
		ShapeRenderer m_shapeRenderer;
	};
}