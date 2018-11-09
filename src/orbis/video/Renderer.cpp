#include "Renderer.h"

namespace orb
{
	void Renderer::draw(orb::Mesh& mesh, const orb::Transform& transform) 
	{
		m_elements.push_back(RenderElement{ mesh, transform });
	}

	void Renderer::display() 
	{
		std::cout << "Begin display" << std::endl;
		for (std::size_t i = 0; i < m_elements.size(); i++) {
			std::cout << "\tBegin element" << i << std::endl;

			std::cout << "\t\tVertices: ";
			for (std::size_t j = 0; j < m_elements[i].mesh.getVertexCount(); j++) {
				std::cout << "(" << m_elements[i].mesh[j].position.x << ", " << m_elements[i].mesh[j].position.y << ") ";
			}
			std::cout << std::endl;

			std::cout << "\t\tIndices: ";
			const std::vector<unsigned int>& indices = m_elements[i].mesh.getIndices();
			for (std::size_t j = 0; j < indices.size(); j++)
				std::cout << indices[j] << " ";
			std::cout << std::endl;

			std::cout << "\t\tTransform position: (" << m_elements[i].transform.getPosition().x << ", " << m_elements[i].transform.getPosition().y << ")" << std::endl;

			std::cout << "\tEnd element " << i << std::endl;
		}
		std::cout << "End display" << std::endl;

		m_elements.clear();
	}


}