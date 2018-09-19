#include "CloseButton.h"

#include "SpriteController.h"

#include "../../Orbis/Orbis.h"
using namespace orb;

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