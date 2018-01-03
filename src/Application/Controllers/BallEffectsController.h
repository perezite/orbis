#pragma once

#include "../../Orbis/Components/Component.h"
using namespace Components;

namespace Controllers
{
	class BallEffectsController : Component
	{
	private:
		enum State
		{
			Idle,
			Exploding_Run
		};

	public:
		// ctor
		BallEffectsController()
			: m_state(State::Idle), m_explosionTimeElapsed(0.0f)
		{}

		// epxloding state
		bool Explode();

	protected:

	private:
		// the current state
		State m_state;

		// explosion time elapsed in seconds
		float m_explosionTimeElapsed;
	};
}