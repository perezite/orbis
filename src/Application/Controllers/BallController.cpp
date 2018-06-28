#include "BallController.h"

#include "../../Base/System/Exception.h"
using namespace base::system;

#include "../../Orbis/Core/LogHelper.h"
#include "../../Orbis/Game/Entity.h"
#include "../../orbis/Input/InputManager.h"
using namespace orbis::core;
using namespace orbis::game;
using namespace input;

#define __STATE_AIMING
#define __STATE_FLYING
#define __STATE_DYING
#define __STATE_PARALYSED

namespace controllers
{
	void BallController::update()
	{
		switch (m_state)
		{
		case State::AimingEnter: aimingEnter(); break;
		case State::AimingRun: aimingRun(); break;
		case State::FlyingEnter: flyingEnter(); break;
		case State::FlyingRun: flyingRun(); break;
		case State::DyingEnter: dyingEnter(); break;
		case State::DyingRun: dyingRun(); break;
		case State::ParalysedEnter: paralysedEnter(); break;
		case State::ParalysedRun: paralysedRun(); break;
		default: throw Exception("State not implemented");
		}
	}

	#ifdef __STATE_AIMING

		void BallController::aimingEnter()
		{
			LogHelper::logMessage("BallController::aimingEnter");
			getParent()->getTransform()->position = Vector2D::Zero;
			m_state = State::AimingRun;
		}

		void BallController::aimingRun()
		{
			LogHelper::logMessage("BallController::aimingRun");
			aimingCurrentAngle = 0.0f;
			getParent()->getTransform()->rotation = aimingCurrentAngle;

			if (InputManager::getInstance()->isTapGoingDown())
				m_state = State::FlyingEnter;
		}

	#endif

	#ifdef __STATE_FLYING
		
		void BallController::flyingEnter()
		{
			LogHelper::logMessage("BallController::flyingEnter");
			m_state = State::FlyingRun;
		}

		void BallController::flyingRun()
		{
			LogHelper::logMessage("BallController::flyingRun");
			if (InputManager::getInstance()->isTapGoingDown())
			{
				m_state = State::DyingEnter;
			}
		}

	#endif

	#ifdef __STATE_DYING

		void BallController::dyingEnter()
		{
			LogHelper::logMessage("BallController::dyingEnter()");
			if (m_ballEffectsController->explode())
				return;

			m_state = State::DyingRun;
		}


		void BallController::dyingRun()
		{
			LogHelper::logMessage("BallController::dyingRun()");

			if (InputManager::getInstance()->isTapGoingDown())
				m_state = State::ParalysedEnter;
		}

	#endif

	#ifdef __STATE_PARALYSED

		void BallController::paralysedEnter()
		{
			LogHelper::logMessage("BallController::paralysedEnter");
			m_state = State::ParalysedRun;

		}

		void BallController::paralysedRun()
		{
			LogHelper::logMessage("BallController::paralysedRun");
			if (InputManager::getInstance()->isTapGoingDown())
				m_state = State::AimingEnter;
		}

	#endif  

	
}
