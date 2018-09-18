#include "CloseButton.h"

#include "SpriteController.h"

#include "../../Orbis/Orbis.h"
using namespace orb::input;
using namespace orb::core;
using namespace orb::game;
using namespace base;

#include <algorithm>

namespace app
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