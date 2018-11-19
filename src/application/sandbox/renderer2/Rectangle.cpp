#include "Rectangle.h"

namespace sb
{
	namespace renderer2
	{
		const Mesh Rectangle::m_mesh({
			Vertex(Vector2f(-0.5f, -0.5f), Color(1, 0, 0, 1)),
			Vertex(Vector2f( 0.5f, -0.5f), Color(0, 1, 0, 1)),
			Vertex(Vector2f( 0.5f,  0.5f), Color(0, 0, 1, 1)),
			Vertex(Vector2f(-0.5f,  0.5f), Color(0, 1, 0, 1))
		});

		void Rectangle::rotate(float dt)
		{ 
			m_transform.rotate(dt * 1.0f); 
		}

	}
}