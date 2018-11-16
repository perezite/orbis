#pragma once

#include "Vertex.h"

#include <vector>

namespace sb
{
	namespace triangle2
	{
		class Mesh
		{
		public:
			Vertex& operator[](std::size_t index) { return m_vertices[index]; }

		private:
			std::vector<Vertex> m_vertices;
		};
	}
}
