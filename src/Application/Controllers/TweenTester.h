#pragma once

#include "../../Orbis/Components/Component.h"
#include "../../Orbis/Game/Entity.h"
#include "../../Orbis/Effects/Tween.h"
using namespace Components;
using namespace Game;
using namespace Effects;

namespace Controllers
{
	// test the animation of an entity's scale using splines
	class TweenTester : public Component
	{
	public:
		// ctor
		TweenTester(Tween* tween, float tweenDuration)
			: Component::Component(), m_tween(tween), m_duration(tweenDuration)
		{ }

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