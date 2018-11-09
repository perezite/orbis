#pragma once

#include "Component.h"

namespace orb
{
	class Shape : public Component
	{
	public:
		Shape(std::size_t numVertices, std::size_t numShapes = 1)
			: m_mesh(numVertices * numShapes)
		{ }

		Vertex& operator[](std::size_t index) { return m_mesh[index]; }

		void draw(Window& window, const Transform& transform = Transform::Identity);

	private:
		Mesh m_mesh;
	};
}