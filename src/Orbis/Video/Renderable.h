#pragma once

#include "../Video/Material.h"
#include "../Video/Mesh.h"
#include "../Game/Transform.h"
#include "../Game/Entity.h"
using namespace Video;
using namespace Game;

#include <iostream>
#include <vector>

namespace Video
{
	// an object being rendered by the render device
	class Renderable
	{
	public:
		// set the transform
		void SetTransform(Transform* transform) { m_transform = transform; }

		// get the transform
		Transform* GetTransform() { return m_transform; }

		// get the mesh
		Mesh* GetMesh() const { return m_mesh; }

		// set the mesh
		void SetMesh(Mesh* mesh) { m_mesh = mesh; }

		// get the material
		Material* GetMaterial() { return &m_material; }

		// check if renederable can be batched with another renderable
		bool IsBatchEqualTo(Renderable* other) { return GetMaterial()->IsBatchEqualTo(other->GetMaterial()); }

	private:
		// the render transforms
		Transform* m_transform;

		// the material
		Material m_material;

		// the mesh
		Mesh* m_mesh;
	};
}