#pragma once

#include "Component.h"
#include "../video/Renderable.h"

namespace orb
{
	// a renderer that draws a shape
	class ShapeRenderer : public Component, public Renderable
	{
	public:
		ShapeRenderer(unsigned int numVertices)
			: m_mesh(numVertices)
		{ };

		Vertex& operator[](std::size_t index) { return m_mesh[index]; }

		Mesh& getMesh() { return m_mesh; }

		void update() { };

	private:
		Mesh m_mesh;
	};
}
