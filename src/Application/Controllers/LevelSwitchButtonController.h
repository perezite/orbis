#pragma once

#include "LevelSwitchButtonController.h"

#include "../../Orbis/Input/InputManager.h"
#include "../../Orbis/Game/Transform.h"
#include "../../Orbis/Game/LevelManager.h"
#include "../../Orbis/Components/Component.h"
using namespace orbis::components;
using namespace orbis::input;
using namespace orbis::game;

namespace controllers
{
	template <class T>
	class LevelSwitchButtonController : public Component
	{
	public:
		// ctor
		LevelSwitchButtonController(bool switchForward) : 
			Component(), m_switchForward(switchForward)
		{}

		// update
		void update()
		{
			InputManager* input = InputManager::getInstance();
			KeyCode switchKey = m_switchForward ? KeyCode::Right : KeyCode::Left;

			if (input->isKeyDown(switchKey) || input->isTapGoingDown(getParent()->getTransform()->getRect()))
				LevelManager::getInstance()->queueLevel(new T());
		}

	private:
		// is switching forward
		bool m_switchForward;
	};
}