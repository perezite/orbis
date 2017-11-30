#include "InputController.h"

#include "SpriteController.h"
using namespace Controllers;

#include "../../Orbis/Input/InputManager.h"
#include "../../Orbis/Core/TimeManager.h"
#include "../../Orbis/Game/Transform.h"
#include "../../Orbis/Game/Entity.h"
using namespace Input;
using namespace Core;
using namespace Game;

#include <algorithm>

namespace
{
	void Rotate(SpriteController* sprite, bool clockwise)
	{
		Transform* transform = sprite->GetParent()->GetTransform();
		float omega = clockwise ? sprite->GetOmega() : -sprite->GetOmega();
		float alpha = transform->GetRotation();
		transform->SetRotation(alpha + TimeManager::GetInstance()->GetDeltaSeconds() * omega);
	}	
}

namespace Controllers
{
	void InputController::Update()
	{
		static InputManager* inputManager = InputManager::GetInstance();

		if (inputManager->IsTapPressed())
		{
			Vector2D tapPosition = inputManager->GetTapPosition();

			// left top tap
			if (tapPosition.GetX() < 0 && tapPosition.GetY() >= 0.0f)
				return;

			// transform negative
			if (tapPosition.GetX() < 0 && tapPosition.GetY() < 0.0f)
			{
				Affect(true);
			}

			// right bottom tap
			if (tapPosition.GetX() >= 0 && tapPosition.GetY() < 0.0f)
			{
				Affect(false);
			}
		}

		if (inputManager->IsTapDown())
		{
			Vector2D tapPosition = inputManager->GetTapPosition();

			// right top tap
			if (tapPosition.GetX() >= 0 && tapPosition.GetY() >= 0.0f)
				Cycle();
		}
	}

	void InputController::Cycle()
	{
		// get new texture
		std::vector<Texture*>::iterator previousTextureIt = std::find(m_inputModeOverlayTextures.begin(), m_inputModeOverlayTextures.end(), m_inputModeOverlaySpriteRenderer->GetTexture());
		std::vector<Texture*>::iterator currentTextureIt = ++previousTextureIt;

		// update sprite renderer
		Texture* nextTexture = currentTextureIt != m_inputModeOverlayTextures.end() ? (*currentTextureIt) : m_inputModeOverlayTextures.front();
		m_inputModeOverlaySpriteRenderer->SetTexture(nextTexture);
	}

	void InputController::Affect(bool positive)
	{
		Rotate(m_yellowBrick, positive);
	}
}