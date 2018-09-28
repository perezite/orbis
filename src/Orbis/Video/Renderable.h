#pragma once

#include "../Video/Material.h"
#include "../Video/Mesh.h"
#include "../Video/Color.h"
#include "../Game/Transform.h"
#include "../Game/Entity.h"

#include <iostream>
#include <vector>

namespace orb
{
	// an object being rendered by the render device
	class Renderable
	{
	public:
		// ctor
		Renderable() : m_mesh(NULL) {}

		// dtor
		virtual ~Renderable()
		{
			if (m_mesh)
				delete m_mesh;
		}

		// set the transform
		void setTransform(Transform* transform) { m_transform = transform; }

		// get the transform
		Transform* getTransform() { return m_transform; }

		// get the mesh
		Mesh* getMesh() const { return m_mesh; }

		// set the mesh
		void setMesh(Mesh* mesh) { m_mesh = mesh; }

		// get the material
		Material* getMaterial() { return &m_material; }

		// check if renederable can be batched with another renderable
		bool isBatchableWith(Renderable* other) { return getMaterial()->isBatchableWith(other->getMaterial()); }

	private:
		// the render transforms
		Transform* m_transform;

		// the material
		Material m_material;

		// the mesh
		Mesh* m_mesh;
	};
}