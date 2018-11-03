#pragma once

#include "Component.h"
#include "../video/Mesh.h"

namespace orb
{
	// a renderer that draws a shape
	class ShapeRenderer : public Component
	{
	public:
		ShapeRenderer(PrimitiveType primitiveType, unsigned int size) 
		 	: m_mesh(primitiveType, size)
		{ };

		void update();

		Vertex& operator[](std::size_t index) { return m_mesh[index]; }

	private:
		Mesh m_mesh;
	};
}
