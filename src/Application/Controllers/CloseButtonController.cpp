#include "CloseButtonController.h"

#include "SpriteController.h"

#include "../../Orbis/Input/InputManager.h"
#include "../../Orbis/Core/LogHelper.h"
#include "../../Orbis/Game/Transform.h"
#include "../../Orbis/Game/Entity.h"
using namespace orbis::input;
using namespace orbis::core;
using namespace orbis::game;
using namespace base::math;

#include <algorithm>

namespace controllers
{
	void CloseButtonController::update()
	{
		InputManager* input = InputManager::getInstance();

		if (input->isTapGoingDown(getParent()->getTransform()->getRect()))
		{
			input->setQuitEvent();
		}
	}
}