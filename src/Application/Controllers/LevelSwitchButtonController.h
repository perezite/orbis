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
		LevelSwitchButtonController(bool switchForward, Level* targetLevel) : 
			Component(), m_switchForward(switchForward), m_targetLevel(targetLevel)
		{}

		// update
		void Update();

	protected:
		// switch to next level
		void SwitchForward();

		// switch to previous level
		void SwitchBackward();

	private:
		// switch forward
		bool m_switchForward;

		// next level
		Level* m_targetLevel;
	};
}