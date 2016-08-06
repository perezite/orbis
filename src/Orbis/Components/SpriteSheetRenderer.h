#pragma once

#include "Component.h"

#include "..\Game\Entity.h"
using namespace Game;

namespace Components
{
	// A wireframe renderer (for testing)
	class SpriteSheetRenderer : public Component
	{
	public:
		// update
		void Update();

		// render
		void Render();
	};
}