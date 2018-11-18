#pragma once

#include "Mesh.h"
#include "Transform.h"

namespace sb
{
	namespace renderer2
	{
		class Rectangle
		{
		public:
			Rectangle()
			{ }

			Rectangle(const Transform& transform_)
				: transform(transform_)
			{ }

			static const Mesh mesh;

			Transform transform;
		};
	}
}