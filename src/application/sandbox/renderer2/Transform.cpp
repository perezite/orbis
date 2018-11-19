#include "Transform.h"

namespace sb
{
	namespace renderer2
	{
		void Transform::setRotation(float alpha)
		{
			rotation = alpha;
		}

		void Transform::rotate(float dAlpha) 
		{
			rotation += dAlpha;
		}

		Vector2f operator*(const Transform & transform, Vector2f right)
		{
			return Vector2f(transform.scale.x * right.x + transform.position.x, transform.scale.y * right.y + transform.position.y);
		}
	}
}