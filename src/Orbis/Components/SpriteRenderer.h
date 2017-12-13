#pragma once

#include "Component.h"

#include "../Video/Texture.h"
#include "../Video/Shader.h"
#include "../Video/Mesh.h"
using namespace Video;

namespace Components
{
	// A renderer which renders a textured quad
	class SpriteRenderer : public Component
	{
	public:
		// ctor
		SpriteRenderer(Texture* texture, bool applyCameraTransformation = true) { SetTexture(texture); m_applyCameraTransformation = applyCameraTransformation; }

		// dtor
		virtual ~SpriteRenderer() { delete m_shader; }

		// update
		void Start();

		// render
		void Render();

		// set the texture
		void SetTexture(Texture* texture) { m_texture = texture; }

		// get the texture
		Texture* GetTexture(void) const { return m_texture; }

		// is the texture transformed in camera coordinates
		bool ApplyCameraTransformation() const { return m_applyCameraTransformation; }

	private:
		// the texture
		Texture* m_texture;

		// the shader
		Shader* m_shader;

		// the mesh
		Mesh* m_mesh;

		// is the camera transformation applied to this sprite
		bool m_applyCameraTransformation;
	};
}