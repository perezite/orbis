#include "LevelSwitchButtonController.h"

#include "../../Orbis/Input/InputManager.h"
#include "../../Orbis/Core/LogHelper.h"
#include "../../Orbis/Game/Transform.h"
#include "../../Orbis/Game/Entity.h"
#include "../../Orbis/Game/LevelManager.h"
using namespace Input;
using namespace Core;
using namespace Game;

namespace Controllers
{
	void LevelSwitchButtonController::Update()
	{
		InputManager* input = InputManager::GetInstance();

		if (input->IsTapGoingDown(GetParent()->GetTransform()->GetRect()))
		{
			LogHelper::LogMessage("LevelSwitchButtonController::Update() clicked %s", m_switchForward ? "forward" : "backward");

			if (m_switchForward)
				SwitchForward();
			else
				SwitchBackward();
		}
	}
	
	void LevelSwitchButtonController::SwitchForward()
	{
		if (m_targetLevel)
			LevelManager::GetInstance()->QueueLevel(m_targetLevel);
	}

	void LevelSwitchButtonController::SwitchBackward()
	{
	}
}