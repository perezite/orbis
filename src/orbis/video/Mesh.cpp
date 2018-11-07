#include "Mesh.h"
#include "../core/Log.h"
#include "../core/Error.h"

#include <iostream>

namespace orb
{
	void Mesh::computeIndices(std::vector<unsigned int>& result, unsigned int offset)
	{
		std::vector<unsigned int> indices;
		for (unsigned int i = 1; i < m_vertices.size() - 1; i++) {
			indices = { i, i + 1, 0 };
			result.insert(result.end(), indices.begin(), indices.end());
		}
	}

	void Mesh::computeVertices(std::vector<float>& result)
	{
		/*std::vector<float> data;
		for (unsigned int i = 0; i < m_vertices.size(); i++) {
			Vector2f pos = m_vertices[i].position;
			Color color = m_vertices[i].color;
			std::vector<float> data = { pos.x, pos.y, color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, m_vertices[i].color. };
			result.push_back(m_vertices[i].position.x);
			result.push_back(m_vertices[i].position.y);
		}*/
	}
}