#pragma once

#include "Component.h"

#include "../Video/Material.h"
#include "../Video/Mesh.h"
using namespace Video;

namespace Components
{
	// Renders a colored quad
	class RectangleRenderer : public Component
	{
	public:
		// ctor
		RectangleRenderer(const Color& color) { m_material.SetColor(color); }

		// update
		void Start();

		// render
		void Render();

	private:
		// the material
		Material m_material;

		// the mesh
		Mesh* m_mesh;
	};
}