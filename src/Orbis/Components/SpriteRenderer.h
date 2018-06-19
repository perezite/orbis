#pragma once

#include "Component.h"

#include "../Video/Texture.h"
#include "../Video/Renderable.h"
using namespace Video;

namespace Components
{
	// A renderer which renders a textured quad
	class SpriteRenderer : public Component
	{
	public:
		// ctor
		SpriteRenderer(Texture* texture);

		// start
		void start();

		// set the texture
		void SetTexture(Texture* texture);

		// get the texture
		Texture* getTexture(void) { return m_renderable.GetMaterial()->getTexture(); }

	private: 
		// the texture
		Texture* m_texture;

		// the renderable
		Renderable m_renderable;
	};
}