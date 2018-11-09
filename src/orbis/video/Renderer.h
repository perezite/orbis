#pragma once

#include "Mesh.h"
#include "Transform.h"
#include "Shader.h"

#include <iostream>

namespace orb
{
	class Renderer 
	{
	public:
		void draw(orb::Mesh& mesh, const orb::Transform& transform);
		
		void print();

		void display();

	protected:
		void initDefaultShader() { };

	private:
		struct RenderElement { orb::Mesh& mesh; const orb::Transform& transform; };

		std::vector<RenderElement> m_elements;

		Shader m_defaultShader;
	};

}