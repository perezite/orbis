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
		TweenTester(Tween* tween)
			: Component::Component(), m_tween(tween)
		{ }

		// override
		void Start();

		// override
		void Update();

	private: 
		// the tween
		Tween* m_tween;
	};
}