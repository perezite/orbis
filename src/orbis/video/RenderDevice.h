#pragma once

#include "Mesh.h"

namespace orb
{
	class RenderDevice
	{
	public:
		void render(const Mesh& mesh);
	};
}