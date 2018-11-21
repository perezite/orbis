#pragma once

#include "Mesh.h"
#include "Transform.h"

namespace sb
{
	namespace triangleRenderer2
	{
		class Triangle
		{
		public:
			Triangle()
			{ }

			Triangle(const Transform& transform_)
				: transform(transform_)
			{ }

			static const Mesh mesh;

			Transform transform;
		};
	}
}
