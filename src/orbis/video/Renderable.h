#pragma once

#include "Mesh.h"

namespace orb
{
	class Renderable
	{
	public:
		Renderable();

		virtual ~Renderable();

		virtual Mesh& getMesh() = 0;
	};
}
