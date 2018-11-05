#include "Mesh.h"
#include "../core/Log.h"
#include "../core/Error.h"

#include <iostream>

namespace orb
{
	void Mesh::computeIndices(std::vector<unsigned int>& result, unsigned int offset)
	{
		for (unsigned int i = 1; i < m_vertices.size() - 1; i++) {
			result.push_back(i);
			result.push_back(i + 1);
			result.push_back(0);
		}
	}

	void Mesh::computeVertices(std::vector<float>& result)
	{
		for (unsigned int i = 0; i < m_vertices.size(); i++) {
			result.push_back(m_vertices[i].position.x);
			result.push_back(m_vertices[i].position.y);
		}
	}
}