#pragma once

#include "Vertex.h"

#include <vector>

namespace sb
{
	namespace triangleRenderer2
	{
		class Mesh
		{
		public:
			Mesh(const std::vector<Vertex>& vertices)
			{
				m_vertices = vertices;
			}

			Vertex& operator[](std::size_t index) { return m_vertices[index]; }

		private:
			std::vector<Vertex> m_vertices;
		};
	}
}
