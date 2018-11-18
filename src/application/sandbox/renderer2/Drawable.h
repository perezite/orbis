#pragma once

#include "Mesh.h"
#include "Transform.h"

namespace sb
{
	namespace renderer2
	{
		class Drawable
		{
		public:
			virtual const Mesh& getMesh() const = 0;

			virtual const Transform& getTransform() const = 0;

		};
	}
}