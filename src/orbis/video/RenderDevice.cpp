#include "RenderDevice.h"
#include "../core/Error.h"

#include <iostream>
#include <algorithm>

namespace orb
{
	void RenderDevice::enable(Renderable& renderable)
	{
		if (std::find(m_renderables.begin(), m_renderables.end(), &renderable) == m_renderables.end())
			m_renderables.push_back(&renderable);
	}

	void RenderDevice::disable(Renderable& renderable)
	{
		m_renderables.erase(std::remove(m_renderables.begin(), m_renderables.end(), &renderable), m_renderables.end());
	}

	void RenderDevice::render()
	{
		ORB_ERROR("Whoopsie");

		std::vector<unsigned int> indices; computeIndices(indices);
		std::vector<float> vertices; computeVertices(vertices);
		printData(indices, vertices);
	}

	void RenderDevice::computeIndices(std::vector<unsigned int>& result)
	{
		std::vector<unsigned int> buffer;
		unsigned int offset = 0;

		for (unsigned int i = 0; i < m_renderables.size(); i++) {
			m_renderables[i]->getMesh().computeIndices(buffer, offset);
			offset += buffer.size();
			result.insert(result.begin(), buffer.begin(), buffer.end());
			buffer.clear();
		}
	}

	void RenderDevice::computeVertices(std::vector<float>& result)
	{
		std::vector<float> buffer;

		for (unsigned int i = 0; i < m_renderables.size(); i++) {
			m_renderables[i]->getMesh().computeVertices(buffer);
			result.insert(result.begin(), buffer.begin(), buffer.end());
			buffer.clear();
		}
	}

	void RenderDevice::printData(std::vector<unsigned int>& indices, std::vector<float>& vertices)
	{
		std::cout << "-- begin RenderDevice::printData()" << std::endl;
		std::cout << "indices";
		for (unsigned int i = 0; i < indices.size(); i++)
			std::cout << " " << indices[i] << " ";
		std::cout << std::endl << "vertices";
		for (unsigned int i = 0; i < vertices.size(); i++)
			std::cout << " " << vertices[i] << " ";
		std::cout << std::endl << "-- end RenderDevice::printData()" << std::endl;

		std::cin.get();
	}

}