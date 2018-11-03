#include "Mesh.h"

#include <iostream>

namespace orb
{
	void Mesh::computeIndices(std::vector<unsigned int>& result, unsigned int offset)
	{
		if (m_primitiveType == PrimitiveType::Triangles) {
			computeTriangleIndices(result, offset);
			return;
		}
		else
			std::cout << "the specified primitive type is not supported";
	}

	void Mesh::computeVertices(std::vector<float>& result)
	{
		for (unsigned int i = 0; i < m_vertices.size(); i++) {
			result.push_back(m_vertices[i].position.x);
			result.push_back(m_vertices[i].position.y);
		}
	}

	void Mesh::computeTriangleIndices(std::vector<unsigned int>& result, unsigned int offset)
	{
		for (unsigned int i = 0; i < m_vertices.size(); i++) 
			result.push_back(i + offset);
	}
}