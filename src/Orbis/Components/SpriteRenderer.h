#pragma once

#include "Component.h"

#include "../Video/Texture.h"
using namespace Video;

namespace Components
{
	// A renderer which renders a triangle
	class SpriteRenderer : public Component
	{
	public:
		// ctor
		SpriteRenderer(Texture* texture, bool applyCameraTransformation = true) { SetTexture(texture); m_applyCameraTransformation = applyCameraTransformation; }

		// update
		void Start();

		// render
		void Render();

		// set the texture
		void SetTexture(Texture* texture) { m_texture = texture; }

		// is the texture transformed in camera coordinates
		bool ApplyCameraTransformation() const { return m_applyCameraTransformation; }

	private:
		// the texture
		Texture* m_texture;

		// is the camera transformation applied to this sprite
		bool m_applyCameraTransformation;
	};
}