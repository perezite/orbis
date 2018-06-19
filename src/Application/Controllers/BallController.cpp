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
#define __STATE_FLYING
#define __STATE_DYING
#define __STATE_PARALYSED

namespace Controllers
{
	void BallController::update()
	{
		switch (m_state)
		{
		case State::Aiming_Enter: AimingEnter(); break;
		case State::Aiming_Run: AimingRun(); break;
		case State::Flying_Enter: FlyingEnter(); break;
		case State::Flying_Run: FlyingRun(); break;
		case State::Dying_Enter: DyingEnter(); break;
		case State::Dying_Run: DyingRun(); break;
		case State::Paralysed_Enter: ParalysedEnter(); break;
		case State::Paralysed_Run: ParalysedRun(); break;
		default: throw Exception("State not implemented");
		}
	}

	#ifdef __STATE_AIMING

		void BallController::AimingEnter()
		{
			LogHelper::logMessage("BallController::AimingEnter");
			getParent()->getTransform()->position = Vector2D::Zero;
			m_state = State::Aiming_Run;
		}

		void BallController::AimingRun()
		{
			LogHelper::logMessage("BallController::AimingRun");
			aimingCurrentAngle = 0.0f;
			getParent()->getTransform()->rotation = aimingCurrentAngle;

			if (InputManager::getInstance()->isTapGoingDown())
				m_state = State::Flying_Enter;
		}

	#endif

	#ifdef __STATE_FLYING
		
		void BallController::FlyingEnter()
		{
			LogHelper::logMessage("BallController::FlyingEnter");
			m_state = State::Flying_Run;
		}

		void BallController::FlyingRun()
		{
			LogHelper::logMessage("BallController::FlyingRun");
			if (InputManager::getInstance()->isTapGoingDown())
			{
				m_state = State::Dying_Enter;
			}
		}

	#endif

	#ifdef __STATE_DYING

		void BallController::DyingEnter()
		{
			LogHelper::logMessage("BallController::DyingEnter()");
			if (m_ballEffectsController->Explode())
				return;

			m_state = State::Dying_Run;
		}


		void BallController::DyingRun()
		{
			LogHelper::logMessage("BallController::DyingRun()");

			if (InputManager::getInstance()->isTapGoingDown())
				m_state = State::Paralysed_Enter;
		}

	#endif

	#ifdef __STATE_PARALYSED

		void BallController::ParalysedEnter()
		{
			LogHelper::logMessage("BallController::ParalysedEnter");
			m_state = State::Paralysed_Run;

		}

		void BallController::ParalysedRun()
		{
			LogHelper::logMessage("BallController::ParalysedRun");
			if (InputManager::getInstance()->isTapGoingDown())
				m_state = State::Aiming_Enter;
		}

	#endif  

	
}
