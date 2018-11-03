#include "../video/Mesh.h"

namespace orb 
{
	// a shape that can be drawn to the screen
	class Shape 
	{
	public:
		Shape(PrimitiveType primitiveType, unsigned int size) : m_mesh(primitiveType, size) { };

		virtual ~Shape() { };

		Vertex& operator[](std::size_t index) { return m_mesh[index]; }

	private: 
		Mesh m_mesh;

	};
}