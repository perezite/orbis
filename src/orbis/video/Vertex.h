#include "Color.h"

#include "../math/Vector2.h"


namespace orb
{
	// a vertex represents one single point in a mesh
	class Vertex
	{
	public:
		Vertex(const Vector2f& position_ = Vector2f::Zero, const Color& color_ = Color::White) : position(position_), color(color_) 
		{};

		virtual ~Vertex() 
		{};

	public:
		Vector2f position;

		Color color;
	};
}