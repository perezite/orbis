#include "Ball.h"

#include "../../Base/Base.h"
using namespace base;

#include "../../Orbis/Orbis.h"
using namespace orb;

#define __STATE_AIMING
#define __STATE_FLYING
#define __STATE_DYING
#define __STATE_PARALYSED

namespace app
{
	void Ball::start()
	{
		m_ballEffects = getParent()->getComponent<BallEffects>();
	}

	void Ball::update()
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

		void Ball::aimingEnter()
		{
			LogUtil::logMessage("Ball::aimingEnter");
			getParent()->getTransform()->position = Vector2D::Zero;
			m_state = State::AimingRun;
		}

		void Ball::aimingRun()
		{
			LogUtil::logMessage("Ball::aimingRun");
			aimingCurrentAngle = 0.0f;
			getParent()->getTransform()->rotation = aimingCurrentAngle;

			if (InputManager::getInstance()->isTapGoingDown())
				m_state = State::FlyingEnter;
		}

	#endif

	#ifdef __STATE_FLYING
		
		void Ball::flyingEnter()
		{
			LogUtil::logMessage("Ball::flyingEnter");
			m_state = State::FlyingRun;
		}

		void Ball::flyingRun()
		{
			LogUtil::logMessage("Ball::flyingRun");
			if (InputManager::getInstance()->isTapGoingDown())
			{
				m_state = State::DyingEnter;
			}
		}

	#endif

	#ifdef __STATE_DYING

		void Ball::dyingEnter()
		{
			LogUtil::logMessage("Ball::dyingEnter()");
			if (m_ballEffects->explode())
				return;

			m_state = State::DyingRun;
		}


		void Ball::dyingRun()
		{
			LogUtil::logMessage("Ball::dyingRun()");

			if (InputManager::getInstance()->isTapGoingDown())
				m_state = State::ParalysedEnter;
		}

	#endif

	#ifdef __STATE_PARALYSED

		void Ball::paralysedEnter()
		{
			LogUtil::logMessage("Ball::paralysedEnter");
			m_state = State::ParalysedRun;

		}

		void Ball::paralysedRun()
		{
			LogUtil::logMessage("Ball::paralysedRun");
			if (InputManager::getInstance()->isTapGoingDown())
				m_state = State::AimingEnter;
		}

	#endif  

	
}
