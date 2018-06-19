#pragma once

#include "LevelSwitchButtonController.h"

#include "../../Orbis/Input/InputManager.h"
#include "../../Orbis/Game/Transform.h"
#include "../../Orbis/Game/LevelManager.h"
#include "../../Orbis/Components/Component.h"
using namespace Components;
using namespace Input;
using namespace Game;

namespace Controllers
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
		void Update()
		{
			InputManager* input = InputManager::getInstance();
			KeyCode switchKey = m_switchForward ? KeyCode::Right : KeyCode::Left;

			if (input->IsKeyDown(switchKey) || input->IsTapGoingDown(GetParent()->getTransform()->GetRect()))
				LevelManager::getInstance()->QueueLevel(new T());
		}

	private:
		// is switching forward
		bool m_switchForward;
	};
}