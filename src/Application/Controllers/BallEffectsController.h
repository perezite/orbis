#pragma once

#include "../../Orbis/Components/Component.h"
using namespace Components;

namespace Controllers
{
	class BallEffectsController : Component
	{
	public:
		// ctor
		BallEffectsController()
			: m_explosionTimeElapsed(0.0f)
		{}

		// epxloding state
		bool Explode();

	protected:

	private:
		// explosion time elapsed in seconds
		float m_explosionTimeElapsed;
	};
}