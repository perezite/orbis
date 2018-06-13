#include "LevelSwitchButtonController.h"

#include "../Levels/LevelFactory.h"
using namespace Levels;

#include "../../Orbis/Input/InputManager.h"
#include "../../Orbis/Game/Transform.h"
#include "../../Orbis/Game/LevelManager.h"
using namespace Input;
using namespace Game;

namespace Controllers
{
	void LevelSwitchButtonController::Update()
	{
		InputManager* input = InputManager::GetInstance();
		KeyCode switchKey = m_switchForward ? KeyCode::Right : KeyCode::Left;

		if (input->IsKeyDown(switchKey) || input->IsTapGoingDown(GetParent()->GetTransform()->GetRect()))
			LevelManager::GetInstance()->QueueLevel(LevelFactory::Instantiate(m_targetLevelName));
	}
}