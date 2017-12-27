#pragma once

#include "Renderer.h"

namespace Components
{
	class NewSpriteRenderer : public Renderer
	{
	public:
		// ctor
		NewSpriteRenderer(Texture* texture);

		// start
		void Start();

		// update
		void Update();

	private: 
		bool m_isGrowing;

		// the texture
		Texture* m_texture;

		static const float MIN_SCALE;
		static const float MAX_SCALE;
	};
}