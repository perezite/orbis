#include "InputModeButtonController.h"

#include "SpriteController.h"

#include "../../Orbis/Orbis.h"
using namespace orb::input;
using namespace orb::core;
using namespace orb::game;
using namespace base::math;

#include <algorithm>

namespace controllers
{
	void InputModeButtonController::update()
	{
		InputManager* inputManager = InputManager::getInstance();

		if (inputManager->isTapGoingDown(getParent()->getTransform()->getRect()))
				cycle();
	}

	void InputModeButtonController::cycle()
	{
		// get current texture
		std::vector<Texture*>::iterator previousTextureIt = std::find(m_textures.begin(), m_textures.end(), m_renderer->getTexture());
		std::vector<Texture*>::iterator currentTextureIt = ++previousTextureIt;

		// update sprite renderer
		Texture* nextTexture = currentTextureIt != m_textures.end() ? (*currentTextureIt) : m_textures.front();
		m_renderer->setTexture(nextTexture);
	}
}