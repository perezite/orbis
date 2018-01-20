#pragma once

#include "../../Orbis/Components/Component.h"
#include "../../Orbis/Game/Entity.h"
#include "../../Orbis/Effects/Tween.h"
using namespace Components;
using namespace Game;
using namespace Effects;

namespace Controllers
{
	// test the animation of an entity's scale using bezier curves 
	class TweenTester : public Component
	{
	public:
		// ctor
		TweenTester(Tween tween, float duration)
			: Component::Component(), m_tween(tween), m_duration(duration), m_elapsed(0.0f)
		{ }

		// override
		void Start();

		// override
		void Update();

	private: 
		// the initial scale
		Vector2D m_initialScale;

		// the tween
		Tween m_tween;

		// duration of the tween
		float m_duration;

		// elapsed tween time
		float m_elapsed;
	};
}