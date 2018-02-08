#pragma once

#include "Component.h"

#include "../Video/Material.h"
#include "../Video/Mesh.h"
#include "../Game/Transform.h"
#include "../Game/Entity.h"
using namespace Video;
using namespace Game;

#include <iostream>
#include <vector>

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

		// get the transforms
		virtual std::vector<Transform> GetRenderTransforms() { return std::vector<Transform> { *GetParent()->GetTransform() }; }

		// the the number of indices of the renderer
		unsigned int GetNumIndices() { return GetMesh()->GetIndices()->size() * GetRenderTransforms().size(); }

		// is the renderer batch equal to another renderer
		bool IsBatchEqualTo(Renderer* other) { return GetMaterial()->IsBatchEqualTo(other->GetMaterial()) && GetRenderTransforms().size() == other->GetRenderTransforms().size(); }

	private:
		// the material
		Material m_material;

		// the mesh
		Mesh* m_mesh;
	};
}