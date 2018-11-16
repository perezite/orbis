#pragma once

#include "Vector2f.h"

namespace sb
{
	namespace triangleRenderer2
	{
		class Transform
		{
		public: 
			Vector2f position;
		};

		Vector2f operator *(const Transform& left, Vector2f right);
	}
}