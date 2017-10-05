#pragma once

#include "Component.h"

namespace Components
{
	// A renderer which renders a triangle
	class TriangleRenderer : public Component
	{
	public:
		// dtor
		~TriangleRenderer();

		// update
		void Start();

		// render
		void Render();
	};
}