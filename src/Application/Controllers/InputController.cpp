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
		float omega = clockwise ? -sprite->GetOmega() : +sprite->GetOmega();
		float alpha = transform->GetRotation();
		transform->SetRotation(alpha + TimeManager::GetInstance()->GetDeltaSeconds() * omega);
	}	

	void Translate(SpriteController* sprite, bool forward)
	{
		float speed = forward ? 0.5f : -0.5f;
		Transform* transform = sprite->GetParent()->GetTransform();
		Vector2D position = transform->GetPosition();
		position = Vector2D(position.GetX() + TimeManager::GetInstance()->GetDeltaSeconds() * speed, position.GetY());
		transform->SetPosition(position);
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

			// transform negative
			if (tapPosition.GetX() < 0 && tapPosition.GetY() < 0.0f)
			{
				Affect(false);
			}

			// right bottom tap
			if (tapPosition.GetX() >= 0 && tapPosition.GetY() < 0.0f)
			{
				Affect(true);
			}
		}

		if (inputManager->IsTapDown())
		{
			Vector2D tapPosition = inputManager->GetTapPosition();

			// left top tap
			if (tapPosition.GetX() < 0 && tapPosition.GetY() >= 0.0f)
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
		std::string texAssetPath = m_inputModeOverlaySpriteRenderer->GetTexture()->GetAssetPath();
		
		if (texAssetPath == "Textures/RotateYellowSprite.png")
		{
			Rotate(m_yellowBrick, positive);
			return;
		}
		if (texAssetPath == "Textures/TranslateBlueSprite.png")
		{
			Translate(m_blueBrick, positive);
			return;
		}

		throw Exception("The given texture asset path is not supported!");
	}
}