#pragma once

#include "PrimitiveType.h"
#include "Vertex.h"

#include <vector>

namespace orb
{
	// a mesh is a bunch of vertices which can be drawn onto the screen
	class Mesh
	{
	public:
		Mesh(unsigned int numVertices) 
			: m_vertices(numVertices)
		{ }

		virtual ~Mesh() { };

		Vertex& operator[](std::size_t index) { return m_vertices[index]; }

		 void computeIndices(std::vector<unsigned int>& result, unsigned int offset);

		 void computeVertices(std::vector<float>& result);

	protected:
		 void computeTriangleIndices(std::vector<unsigned int>& result, unsigned int offset);

	private:
		PrimitiveType m_primitiveType;

		std::vector<Vertex> m_vertices;
	};
}

