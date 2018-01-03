#pragma once

#include "BallEffectsController.h"

#include "../../Orbis/Components/Component.h"
using namespace Components;

namespace Controllers
{
	class BallController : public Component
	{
	private:
		enum State
		{
			Aiming_Enter,
			Aiming_Run,
			Flying_Enter,
			Flying_Run,
			Dying_Enter,
			Dying_Run
		};

	public:
		// ctor
		BallController() 
			: m_state(State::Aiming_Enter), aimingCurrentAngle(0.0f)
		{}

		// override
		void Update();

		// set the ball effects controller
		void SetBallEffectsController(BallEffectsController* ballEffectsController) { m_ballEffectsController = ballEffectsController; }

		// enter the aiming state
		void AimingEnter();
	
		// run the aiming state
		void AimingRun();

		// enter the flying state
		void FlyingEnter();

		// run the flying state
		void FlyingRun();

		// enter the dying state
		void DyingEnter();

		// run the dying state
		void DyingRun();

	private:
		// current state
		State m_state;

		// the current aiming angle
		float aimingCurrentAngle;

		// the ball effects controller
		BallEffectsController* m_ballEffectsController;
	};
}