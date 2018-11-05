#pragma once

#include "Renderable.h"

#include <vector>

namespace orb
{
	// the device used for rendering graphics
	class RenderDevice
	{
	public:
		void enable(Renderable& renderable);

		void disable(Renderable& renderable);

		void render();

	protected:
		void computeIndices(std::vector<unsigned int>& result);

		void computeVertices(std::vector<float>& result);

		void printData(std::vector<unsigned int>& indices, std::vector<float>& vertices);

	private:
		std::vector<Renderable*> m_renderables;
	};
}