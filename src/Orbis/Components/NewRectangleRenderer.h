#pragma once

#include "Renderer.h"

namespace Components
{
	class NewRectangleRenderer : public Renderer
	{
	public:
		// ctor
		NewRectangleRenderer();

		// update
		void Update();

	private:
		bool m_isGrowing;

		// the flat color
		Color m_color;

		static const float MIN_BLOCK_SCALE;
		static const float MAX_BLOCK_SCALE;
	};
}