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
		SpriteRenderer(Texture* texture) { SetTexture(texture); }

		// update
		void Start();

		// render
		void Render();

		// set the texture
		void SetTexture(Texture* texture) { m_texture = texture; }

	private:
		// the texture
		Texture* m_texture;
	};
}