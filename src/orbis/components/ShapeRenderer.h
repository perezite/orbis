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

		Vertex& operator[](std::size_t index) { return m_mesh[index]; }

		void update() { };

		void render();

	private:
		Mesh m_mesh;
	};
}
