#pragma once

#include "Mesh.h"

namespace orb
{
	class Renderable
	{
	public:
		Renderable(unsigned int numVertices);

		virtual ~Renderable();

	private:
		Mesh m_mesh;
	};
}
