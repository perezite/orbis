#pragma once

#include "../../Orbis/Components/Component.h"
#include "../../Orbis/Game/Entity.h"
#include "../../Orbis/Effects/Tween.h"
using namespace orb;

namespace app
{
	// test the animation of an entity's scale using splines
	class WobbleBrickEffect : public Component
	{
	public:
		// ctor
		WobbleBrickEffect(std::string tween, float tweenDuration);

		// override
		void start();

		// override
		void update();

	private: 
		// the tween
		Tween* m_tween;

		// the tween duration
		float m_duration;
	};
}