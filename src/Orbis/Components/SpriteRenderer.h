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

		// update
		void Update();

		// set the texture
		// TODO: remove after refactoring
		void SetTexture(Texture* texture) { }

		// get the texture
		// TODO: remove after refactoring
		Texture* GetTexture(void) const { return NULL; }

	private:
		// TODO: remove after refactoring
		bool m_isGrowing;

		// the texture
		Texture* m_texture;

		// TODO: remove after refactoring
		static const float MIN_SCALE;
		static const float MAX_SCALE;
	};
}