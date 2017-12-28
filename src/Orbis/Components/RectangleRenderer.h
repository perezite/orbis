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

	private:
		// the color 
		Color m_color;
	};
}