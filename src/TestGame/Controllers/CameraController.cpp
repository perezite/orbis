#include "CameraController.h"

#include "..\..\Orbis\Game\Entity.h"
using namespace Game;

#include "..\..\Orbis\Input\InputManager.h"
using namespace Input;

#include "..\..\Orbis\Math\MathHelper.h"
using namespace Math;

#include <cmath>
#include <iostream>

namespace Controllers
{
	void CameraController::Start()
	{
		m_isHeadingLeft = false;
		m_isScalingDown = false;
		m_initialScale = GetParent()->GetTransform()->GetScale();
	}

	void CameraController::Update()
	{
		float linearSpeed = 0.1f;
		float angularSpeed = 0.1f;
		float scaleSpeed = 0.95f;
		InputManager* inputManager = InputManager::GetInstance();

		// apply transforms
		if (inputManager->IsKeyDown(KeyCode::i))
		{
			Vector2D deltaPosition = Vector2D(m_isHeadingLeft ? -linearSpeed : linearSpeed, 0.0f);
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
			float scaleFactor = m_isScalingDown ? scaleSpeed : 1.0f / scaleSpeed;
			Vector2D scale = GetParent()->GetTransform()->GetScale();
			GetParent()->GetTransform()->SetScale(scale * scaleFactor);
		}

		if (inputManager->IsKeyDown(KeyCode::u))
		{
			Transform* transform = GetParent()->GetTransform();
			transform->SetRotation(0.0f);
			transform->SetPosition(Vector2D::Zero);
			transform->SetScale(m_initialScale);
		}

		// change linear direction
		if (std::abs(GetParent()->GetTransform()->GetPosition().GetX()) > 3.0f)
			m_isHeadingLeft = !m_isHeadingLeft;

		// change scale up/down
		if (GetParent()->GetTransform()->GetScale().GetX() < m_initialScale.GetX() * 0.1f)
			m_isScalingDown = false;
		if (GetParent()->GetTransform()->GetScale().GetX() > m_initialScale.GetX() * 1.5f)
			m_isScalingDown = true;
	}
}
