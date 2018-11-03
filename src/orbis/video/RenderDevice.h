#pragma once

#include "Mesh.h"
#include "Material.h"

#include <vector>

namespace orb
{
	// the device used for rendering graphics
	class RenderDevice
	{
	public:
		void render(Mesh* mesh);

		void finalize();

	protected:
		void computeIndices(std::vector<unsigned int>& result);

		void computeVertices(std::vector<float>& result);

	private:
		std::vector<Mesh*> m_meshes;
	};
}