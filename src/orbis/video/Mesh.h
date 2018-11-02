#include "PrimitiveType.h"
#include "Vertex.h"

#include <vector>

namespace orb
{
	// a mesh is a collection of vertices which can be drawn on the screen
	class Mesh
	{
	public:
		Mesh(PrimitiveType primitiveType, unsigned int size) 
			: m_primitiveType(primitiveType), m_vertices(size)
		{}

		virtual ~Mesh() 
		{};

		Vertex& operator[](std::size_t index) { return m_vertices[index]; }

	private:
		PrimitiveType m_primitiveType;

		std::vector<Vertex> m_vertices;
	};
}

