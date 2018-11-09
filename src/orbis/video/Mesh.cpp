#include "Mesh.h"

namespace orb
{
	void Mesh::calculateIndices() 
	{
		for (std::size_t i = 0; i < m_vertices.size(); i++)
			m_indices[i] = i;
	}
}