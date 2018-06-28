#pragma once

#include "Component.h"

#include "../Video/Color.h"
#include "../Video/Renderable.h"
using namespace orb::video;

namespace orb
{
	namespace components
	{
		// Renders a colored quad
		class RectangleRenderer : public Component
		{
		public:
			// ctor
			RectangleRenderer(const Color& color) : Component() { m_color = color; }

			// start
			void start();

		private:
			// the color 
			Color m_color;

			// the renderable
			Renderable m_renderable;
		};
	}
}