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
			State_PrepareAiming,
			State_Aiming,
			State_Idle
		};

	public:
		// ctor
		BallController() 
			: m_currentState(State::State_PrepareAiming), aimingCurrentAngle(0.0f)
		{}

		// override
		void Update();

		// prepare the aiming state
		void PrepareAiming();
	
		// the aiming state
		void Aiming();

	private:	
		// the aiming angle in degrees
		static const float AIMING_ANGLE;

		// the aiming rotational velocity in degrees
		static const float AIMING_OMEGA;

	private:
		// current state
		State m_currentState;

		// the current aiming angle
		float aimingCurrentAngle;
	};
}