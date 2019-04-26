#include "InputModeButton.h"

#include "SpriteController.h"

#include "../../Orbis/Orbis.h"
using namespace orb;

#include <algorithm>

namespace app
{
	void InputModeButton::update()
	{
		InputManager* inputManager = InputManager::instance();

		if (inputManager->isTapGoingDown(getParent()->getTransform()->getRect()))
			cycle();
	}

	void InputModeButton::cycle()
	{
		if (m_spriteRenderer) {
			std::vector<std::string>::iterator current = std::find(m_textures.begin(), m_textures.end(), m_spriteRenderer->getTexturePath());
			if (current != m_textures.end()) 
				current++;
			std::string newTexture = current != m_textures.end() ? (*current) : m_textures.front();
			m_spriteRenderer->setTexture(newTexture);
		}
	}
}