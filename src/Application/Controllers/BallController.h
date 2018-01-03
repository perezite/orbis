#pragma once

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
			Aiming_Exit
		};

	public:
		// ctor
		BallController() 
			: m_currentState(State::Aiming_Enter), aimingCurrentAngle(0.0f)
		{}

		// override
		void Update();

		// enter the aiming state
		void AimingEnter();
	
		// run the aiming state
		void AimingRun();

		// exit the aiming state
		void AimingExit();

	private:
		// current state
		State m_currentState;

		// the current aiming angle
		float aimingCurrentAngle;
	};
}