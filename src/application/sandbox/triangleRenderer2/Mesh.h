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

			std::size_t getSize() const { return m_vertices.size(); }

			const Vertex& operator[](std::size_t index) const { return m_vertices[index]; }

		private:
			std::vector<Vertex> m_vertices;
		};
	}
}