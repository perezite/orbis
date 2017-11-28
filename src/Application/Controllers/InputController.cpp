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

		if (inputManager->IsTapDown())
		{
			Vector2D tapPosition = inputManager->GetTapPosition();

			// left top tap
			if (tapPosition.GetX() < 0 && tapPosition.GetY() >= 0.0f)
				return;

			// right top tap
			if (tapPosition.GetX() >= 0 && tapPosition.GetY() >= 0.0f)
				return;

			// transform negative
			if (tapPosition.GetX() < 0 && tapPosition.GetY() < 0.0f)
			{
				Rotate(m_yellowBrick, true);
			}

			// right bottom tap
			if (tapPosition.GetX() >= 0 && tapPosition.GetY() < 0.0f)
			{
				Rotate(m_yellowBrick, false);
			}
		}
	}
}