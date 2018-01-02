#include "BallController.h"

#include "../../Base/System/Exception.h"
using namespace System;

#include "../../Orbis/Core/LogHelper.h"
#include "../../Orbis/Game/Entity.h"

using namespace Core;
using namespace Game;

namespace Controllers
{
	static const float AIMING_ANGLE = 70.0f;

	static const float AIMING_OMEGA = 150.0f;

	void BallController::Update()
	{
		switch (m_currentState)
		{
		case State::State_PrepareAiming:
			PrepareAiming();
			break;
		case State::State_Aiming:
			Aiming();
			break;
		default:
			throw Exception("Not implemented");
		}
	}

	void BallController::PrepareAiming()
	{
		LogHelper::LogMessage("BallController::PrepareAiming");
		GetParent()->GetTransform()->position = Vector2D::Zero;
		m_currentState = State::State_Aiming;
	}

	void BallController::Aiming()
	{
		LogHelper::LogMessage("BallController::Aiming");
		aimingCurrentAngle = 0.0f;
		GetParent()->GetTransform()->rotation = aimingCurrentAngle;

	}
}
