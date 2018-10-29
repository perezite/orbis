#pragma once

#include "LevelSwitchButtonController.h"

#include "../../Orbis/Input/InputManager.h"
#include "../../Orbis/Game/Transform.h"
#include "../../Orbis/Game/LevelManager.h"
#include "../../Orbis/Components/Component.h"
using namespace orb;

namespace app
{
	template <class T>
	class LevelSwitchButtonController : public Component
	{
	public:
		// ctor
		LevelSwitchButtonController(bool switchForward) : 
			Component(), m_switchForward(switchForward)
		{}

		// updateLevel
		void update()
		{
			InputManager* input = InputManager::instance();
			KeyCode switchKey = m_switchForward ? KeyCode::Right : KeyCode::Left;

			if (input->isKeyDown(switchKey) || input->isTapGoingDown(getParent()->getTransform()->getRect()))
				LevelManager::instance()->queueLevel(new T());
		}

	private:
		// is switching forward
		bool m_switchForward;
	};
}