#pragma once

#include "..\Game\Entity.h"
#include "..\Game\Component.h"
using namespace Game;

namespace Components
{
	// A test renderer which renders a small box at the position of the entity
	class TestRenderer : public Component
	{
	public:
		// update
		void Update();

		// render
		void Render();
	};
}