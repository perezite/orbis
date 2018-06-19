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
			Aiming_Enter, Aiming_Run,
			Flying_Enter, Flying_Run,
			Dying_Enter, Dying_Run,
			Paralysed_Enter, Paralysed_Run
		};

	public:
		// ctor
		BallController() 
			: m_state(State::Aiming_Enter), aimingCurrentAngle(0.0f)
		{}

		// override
		void update();

		// set the ball effects controller
		void SetBallEffectsController(BallEffectsController* ballEffectsController) { m_ballEffectsController = ballEffectsController; }

		// aiming
		void AimingEnter();	void AimingRun();

		// flying
		void FlyingEnter(); void FlyingRun();

		// dying
		void DyingEnter();	void DyingRun();

		// enter the paralysed state
		void ParalysedEnter();	void ParalysedRun();

	private:
		// current state
		State m_state;

		// the current aiming angle
		float aimingCurrentAngle;

		// the ball effects controller
		BallEffectsController* m_ballEffectsController;
	};
}