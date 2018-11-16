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
			static Mesh mesh;

			Transform transform;
		};
	}
}
