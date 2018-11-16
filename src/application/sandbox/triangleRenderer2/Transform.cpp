#include "Transform.h"

namespace sb
{
	namespace triangleRenderer2
	{
		Vector2f operator*(const Transform & left, Vector2f right)
		{
			return Vector2f((left.position.x + right.x) * left.scale.x, (left.position.y + right.y) * left.scale.y);
		}
	}
}