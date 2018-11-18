#pragma once

#include "Vertex.h"
#include <vector>

namespace orb
{
	class Mesh
	{
	public:
		Mesh(std::size_t numVertices, std::size_t numElements = 1)
			: m_indices(numVertices * numElements), m_vertices(numVertices * numElements)
		{
			calculateIndices();
		}

		Vertex& operator[](std::size_t index) { return m_vertices[index]; }

		std::size_t getVertexCount() const { return m_vertices.size(); }

		const std::vector<unsigned int>& getIndices() const { return m_indices; }

		std::size_t getIndexCount() const { return m_indices.size(); }

	protected:
		void calculateIndices();

	private:

		std::vector<unsigned int> m_indices;

		std::vector<Vertex> m_vertices;
	};
}