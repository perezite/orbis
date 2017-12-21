#pragma once

#include "Mesh.h"
#include "Material.h"

#include "../Game/Transform.h"
using namespace Game;

namespace Video
{
	class RenderBatch
	{
	public:
		// ctor
		RenderBatch(const Transform& transform, Mesh* mesh, Material* material)
			: m_mesh(mesh), m_material(material)
		{
			m_transform = transform;
		}

		// get transform
		const Transform& GetTransform() const { return m_transform; }

		// get mesh
		Mesh* GetMesh() const { return m_mesh; }

		// get material
		Material* GetMaterial() const { return m_material; }

	private:
		// the transform
		Transform m_transform;
		
		// the mesh
		Mesh* m_mesh;
		
		// the material
		Material* m_material;
	};
}