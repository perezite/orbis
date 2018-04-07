#include "CloseButtonController.h"

#include "SpriteController.h"

#include "../../Orbis/Input/InputManager.h"
#include "../../Orbis/Core/LogHelper.h"
#include "../../Orbis/Game/Transform.h"
#include "../../Orbis/Game/Entity.h"
using namespace Input;
using namespace Core;
using namespace Game;
using namespace Math;

#include <algorithm>

namespace Controllers
{
	void CloseButtonController::Update()
	{
		InputManager* input = InputManager::GetInstance();

		if (input->IsTapGoingDown(GetParent()->GetTransform()->GetRect()))
		{
			input->SetQuitEvent();
		}
	}
}