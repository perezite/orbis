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
			virtual ~Drawable() { };

			virtual const Mesh& getMesh() = 0;

			virtual Transform& getTransform() = 0;
		};
	}
}