#include "CloseButton.h"

#include "SpriteController.h"

#include "../../Orbis/Orbis.h"
using namespace orb::input;
using namespace orb::core;
using namespace orb::game;
using namespace base::math;

#include <algorithm>

namespace controllers
{
	void CloseButton::update()
	{
		InputManager* input = InputManager::getInstance();

		if (input->isTapGoingDown(getParent()->getTransform()->getRect()))
		{
			input->setQuitEvent();
		}
	}
}