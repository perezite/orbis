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
			:
		{ };

		Vertex& operator[](std::size_t index) { return m_mesh[index]; }

		void update() { };
	};
}
