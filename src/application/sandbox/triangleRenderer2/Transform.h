#pragma once

#include "Vector2f.h"

namespace sb
{
	namespace triangleRenderer2
	{
		class Transform
		{
		public:
			Transform(Vector2f position_, Vector2f scale_) 
				: position(position_), scale(scale_)
			{ }

			Transform()
			{ }

			Vector2f position;

			Vector2f scale;
		};

		Vector2f operator *(const Transform& left, Vector2f right);
	}
}