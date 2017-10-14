#pragma once

#include "Component.h"

namespace Components
{
	// A renderer which renders a triangle
	class SpriteRenderer : public Component
	{
	public:
		// dtor
		~SpriteRenderer();

		// update
		void Start();

		// render
		void Render();
	};
}