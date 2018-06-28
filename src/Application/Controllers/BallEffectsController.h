#pragma once

#include "../../Orbis/Components/Component.h"
using namespace orbis::components;

namespace controllers
{
	class BallEffectsController : Component
	{
	public:
		// ctor
		BallEffectsController()
			: m_explosionTimeElapsed(0.0f)
		{}

		// epxloding state
		bool explode();

	protected:

	private:
		// explosion time elapsed in seconds
		float m_explosionTimeElapsed;
	};
}