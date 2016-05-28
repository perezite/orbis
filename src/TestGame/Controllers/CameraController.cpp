#include "CameraController.h"

#include "..\..\Orbis\Game\Entity.h"
using namespace Game;

#include "..\..\Orbis\Input\InputManager.h"
using namespace Input;

#include <cmath>
#include <iostream>

namespace Controllers
{
	CameraController::CameraController() : isHeadingLeft(false), isScalingDown(false)
	{ }

	void CameraController::Update()
	{
		float linearSpeed = 0.1f;
		float angularSpeed = 0.1f;
		float scaleSpeed = 0.1f;
		InputManager* inputManager = InputManager::GetInstance();

		// apply transforms
		if (inputManager->IsKeyDown(KeyCode::i))
		{
			Vector2D deltaPosition = Vector2D(isHeadingLeft ? -linearSpeed : linearSpeed, 0.0f);
			Vector2D position = GetParent()->GetTransform()->GetPosition();
			GetParent()->GetTransform()->SetPosition(position + deltaPosition);
		}
		if (inputManager->IsKeyDown(KeyCode::o))
		{
			float rotation = GetParent()->GetTransform()->GetRotation();
			GetParent()->GetTransform()->SetRotation(rotation + angularSpeed);
		}
		if (inputManager->IsKeyDown(KeyCode::p))
		{
			Vector2D deltaScale = isScalingDown ? Vector2D(-scaleSpeed, -scaleSpeed) : Vector2D(scaleSpeed, scaleSpeed);
			Vector2D scale = GetParent()->GetTransform()->GetScale();
			GetParent()->GetTransform()->SetScale(scale + deltaScale);
		}

		// change linaer direction
		if (std::abs(GetParent()->GetTransform()->GetPosition().GetX()) > 3.0f)
			isHeadingLeft = !isHeadingLeft;

		// change scale up/down
		if (GetParent()->GetTransform()->GetScale().GetX() < 1.0f)
			isScalingDown = false;
		if (GetParent()->GetTransform()->GetScale().GetX() > 5.0f)
			isScalingDown = true;
	}
}
