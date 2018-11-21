#include "Transform.h"

#define _USE_MATH_DEFINES
#include "math.h"

namespace sb
{
	namespace renderer2
	{
		void Transform::setRotation(float alpha)
		{
			rotation = fmod(alpha, 2.0f * (float)M_PI);
		}

		void Transform::rotate(float dAlpha) 
		{
			rotation += dAlpha;
		}

		Vector2f operator*(const Transform & transform, Vector2f right)
		{/*
			float ca = cosf(transform.rotation); 
			float sa = sinf(transform.rotation);*/

			return Vector2f(transform.scale.x * right.x + transform.position.x, transform.scale.y * right.y + transform.position.y);
			//return Vector2f(
			//	(transform.scale.x * right.x * ca - transform.scale.x * right.y * sa) + transform.position.x,
			//	(transform.scale.y * right.x * sa + transform.scale.y * right.y * ca) + transform.position.y
			//);
		}
	}
}