#pragma once

#include "BallEffects.h"

#include "../../Orbis/Components/Component.h"
using namespace orb::components;

namespace app
{
	class Ball : public Component
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
		Ball() 
			: m_state(State::AimingEnter), aimingCurrentAngle(0.0f)
		{}

		// override
		void update();

		// set the ball effects controller
		void setBallEffectsController(BallEffects* ballEffectsController) { m_ballEffectsController = ballEffectsController; }

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
		BallEffects* m_ballEffectsController;
	};
}