#pragma once

#include "Renderer.h"

namespace Components
{
	class NewSpriteRenderer : public Renderer
	{
	public:
		// ctor
		NewSpriteRenderer(Texture* texture);

		// update
		void Update();
	private: 
		bool m_isGrowing;

		static const float MIN_BLOCK_SCALE;
		static const float MAX_BLOCK_SCALE;
	};
}