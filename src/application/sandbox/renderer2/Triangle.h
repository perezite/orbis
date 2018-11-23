#pragma once

#include "Mesh.h"
#include "Transform.h"

namespace sb
{
	namespace renderer2
	{
		class Triangle
		{
		public:
			Triangle()
			{ }

			Triangle(const Vector2f& position, const Vector2f scale)
				: transform(position, scale)
			{ }

			static const Mesh mesh;

			Transform transform;
		};
	}
}
