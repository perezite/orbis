#include "Transform.h"

namespace sb
{
	namespace triangle2
	{
		Vector2f operator*(const Transform & left, Vector2f right)
		{
			return Vector2f(left.position.x + right.x, left.position.y + right.y);
		}

	}
}