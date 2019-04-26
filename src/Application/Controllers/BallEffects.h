#pragma once

#include "../../Orbis/Components/Component.h"
using namespace orb;

namespace app
{
	class BallEffects : public Component
	{
	public:
		// ctor
		BallEffects()
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