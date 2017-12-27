#pragma once

#include "Component.h"

#include "../Video/Material.h"
#include "../Video/Mesh.h"
using namespace Video;

#include <iostream>

namespace Components
{
	// an abstract renderer component
	class Renderer : public Component
	{
	public:
		// get the mesh
		Mesh* GetMesh() const { return m_mesh; }

		// set the mesh
		void SetMesh(Mesh* mesh) { m_mesh = mesh; }

		// get the material
		Material* GetMaterial() { return &m_material; }

	private: 
		// the material
		Material m_material;

		// the mesh
		Mesh* m_mesh;
	};
}