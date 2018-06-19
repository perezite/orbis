#pragma once

#include "BallEffectsController.h"

#include "../../Orbis/Components/Component.h"
using namespace Components;

namespace Controllers
{
	class BallController : public Component
	{
	private:
		enum class State
		{
			AimingEnter, AimingRun,
			FlyingEnter, FlyingRun,
			DyingEnter, DyingRun,
			ParalysedEnter, ParalysedRun
		};

	public:
		// ctor
		BallController() 
			: m_state(State::AimingEnter), aimingCurrentAngle(0.0f)
		{}

		// override
		void update();

		// set the ball effects controller
		void setBallEffectsController(BallEffectsController* ballEffectsController) { m_ballEffectsController = ballEffectsController; }

		// aiming
		void aimingEnter();	void aimingRun();

		// flying
		void flyingEnter(); void flyingRun();

		// dying
		void dyingEnter();	void dyingRun();

		// enter the paralysed state
		void paralysedEnter();	void paralysedRun();

	private:
		// current state
		State m_state;

		// the current aiming angle
		float aimingCurrentAngle;

		// the ball effects controller
		BallEffectsController* m_ballEffectsController;
	};
}