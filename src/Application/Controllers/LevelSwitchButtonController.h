#pragma once

#include "../../Orbis/Components/Component.h"
#include "../../Orbis/Components/SpriteRenderer.h"
#include "../../Orbis/Game/Level.h"
using namespace Components;
using namespace Game;

namespace Controllers
{
	class LevelSwitchButtonController : public Component
	{
	public:
		LevelSwitchButtonController(Level* targetLevel) : 
			Component(), m_targetLevel(targetLevel)
		{}

		// update
		void Update();

	private:
		// next level
		Level* m_targetLevel;
	};
}