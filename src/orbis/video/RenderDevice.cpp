#include "RenderDevice.h"

#include <iostream>

namespace orb
{
	void RenderDevice::render(Mesh* mesh)
	{
		m_meshes.push_back(mesh);
	}

	void RenderDevice::finalize()
	{
		std::vector<unsigned int> indices; computeIndices(indices);
		std::vector<float> vertices; computeVertices(vertices);

		std::cout << "-- begin RenderDevice::finalize()" << std::endl;
		std::cout << "indices";
		for (unsigned int i = 0; i < indices.size(); i++)
			std::cout << " " << indices[i] << " ";
		std::cout << std::endl << "vertices";
		for (unsigned int i = 0; i < vertices.size(); i++)
			std::cout << " " << vertices[i] << " ";
		std::cout << std::endl << "-- end RenderDevice::finalize()" << std::endl;

		std::cin.get();

		m_meshes.clear();
	}

	void RenderDevice::computeIndices(std::vector<unsigned int>& result)
	{
		std::vector<unsigned int> buffer;
		unsigned int offset = 0;

		for (unsigned int i = 0; i < m_meshes.size(); i++) {
			m_meshes[i]->computeIndices(buffer, offset);
			offset += buffer.size();
			result.insert(result.begin(), buffer.begin(), buffer.end());
			buffer.clear();
		}
	}

	void RenderDevice::computeVertices(std::vector<float>& result)
	{
		std::vector<float> buffer;

		for (unsigned int i = 0; i < m_meshes.size(); i++) {
			m_meshes[i]->computeVertices(buffer);
			result.insert(result.begin(), buffer.begin(), buffer.end());
			buffer.clear();
		}
	}
}