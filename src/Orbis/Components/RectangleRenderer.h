#pragma once

#include "Renderer.h"

namespace Components
{
	// Renders a colored quad
	class RectangleRenderer : public Renderer
	{
	public:
		// ctor
		RectangleRenderer(const Color& color) : Renderer() { m_color = color; }

		// start
		void Start();

		// update
		// TODO: Remove after refactoring
		void Update();

	private:
		// the color 
		Color m_color;

		// TODO: remove after refactorig 
		bool m_isGrowing;

		// TODO: remove after refactoring
		static const float MIN_SCALE;
		static const float MAX_SCALE;
	};
}