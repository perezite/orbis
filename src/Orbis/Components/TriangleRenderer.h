#pragma once

#include "Component.h"

namespace Components
{
	// A renderer which renders a triangle
	class TriangleRenderer : public Component
	{
	public:
		// update
		void Update();

		// render
		void Render();
	};
}