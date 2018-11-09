#pragma once

#include "Mesh.h"
#include "Transform.h"

#include <iostream>

namespace orb
{
	class Renderer 
	{

	private:
		struct RenderElement { orb::Mesh& mesh; const orb::Transform& transform; };

	public:
		void draw(orb::Mesh& mesh, const orb::Transform& transform);
		
		void display();

	private:
		std::vector<RenderElement> m_elements;
	};

}