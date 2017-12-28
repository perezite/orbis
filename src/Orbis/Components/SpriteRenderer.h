#pragma once

#include "Renderer.h"

#include "../Video/Texture.h"
using namespace Video;

namespace Components
{
	// A renderer which renders a textured quad
	class SpriteRenderer : public Renderer
	{
	public:
		// ctor
		SpriteRenderer(Texture* texture);

		// start
		void Start();

		// set the texture
		void SetTexture(Texture* texture);

		// get the texture
		Texture* GetTexture(void) { return GetMaterial()->GetTexture(); }

	private: 
		// the texture
		Texture* m_texture;
	};
}