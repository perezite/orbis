#pragma once

#include "SpriteController.h"

#include "../../Orbis/Components/Component.h"
using namespace Components;

namespace Controllers
{
	class InputController : public Component 
	{
	public:
		// update
		void Update();

		// set yellow brick
		void SetYellowBlock(SpriteController* const yellowBrick) { m_yellowBrick = yellowBrick; }

	private:
		SpriteController* m_yellowBrick;
	};
}