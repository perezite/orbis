#pragma once

#include "Component.h"

#include "../Video/Material.h"
#include "../Video/Mesh.h"
using namespace Video;

#include "../../Orbis/Game/Entity.h"
#include "../../Orbis/Game/TransformSpace.h"
using namespace Game;

namespace Components
{
	// A renderer which renders a textured quad
	class SpriteRenderer : public Component
	{
	public:
		// ctor
		SpriteRenderer(Texture* texture) { m_material.SetTexture(texture);}

		// update
		void Start();

		// render
		void Render();

		// set the texture
		void SetTexture(Texture* texture) { m_material.SetTexture(texture); }

		// get the texture
		Texture* GetTexture(void) const { return m_material.GetTexture(); }

	private:
		// the material
		Material m_material;

		// the mesh
		Mesh* m_mesh;
	};
}