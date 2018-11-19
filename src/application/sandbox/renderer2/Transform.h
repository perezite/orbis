#pragma once

#include "Vector2f.h"

namespace sb
{
	namespace renderer2
	{
		class Transform
		{
		public:
			Transform(Vector2f position_, Vector2f scale_)
				: position(position_), scale(scale_)
			{ }

			Transform()
			{ }

			void setRotation(float alpha);

			void rotate(float dAlpha);

			Vector2f position;

			Vector2f scale;

			float rotation;
		};

		Vector2f operator *(const Transform& transform, Vector2f position);
	}
}