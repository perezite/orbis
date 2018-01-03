#include "BallController.h"

#include "../../Base/System/Exception.h"
using namespace System;

#include "../../Orbis/Core/LogHelper.h"
#include "../../Orbis/Game/Entity.h"
#include "../../orbis/Input/InputManager.h"
using namespace Core;
using namespace Game;
using namespace Input;

#define __STATE_AIMING

namespace Controllers
{
	void BallController::Update()
	{
		switch (m_currentState)
		{
		case State::Aiming_Enter:
			AimingEnter();
			break;
		case State::Aiming_Run:
			AimingRun();
			break;
		case State::Aiming_Exit:
			AimingExit();
			break;
		default:
			throw Exception("State not implemented");
		}
	}

	#ifdef __STATE_AIMING

		void BallController::AimingEnter()
		{
			LogHelper::LogMessage("BallController::AimingEnter");
			GetParent()->GetTransform()->position = Vector2D::Zero;
			m_currentState = State::Aiming_Run;
		}

		void BallController::AimingRun()
		{
			LogHelper::LogMessage("BallController::AimingRun");
			aimingCurrentAngle = 0.0f;
			GetParent()->GetTransform()->rotation = aimingCurrentAngle;

			if (InputManager::GetInstance()->IsTapGoingDown())
				m_currentState = State::Aiming_Exit;
		}

		void BallController::AimingExit()
		{
			LogHelper::LogMessage("BallController::AimingExit");
		}

	#endif

}
