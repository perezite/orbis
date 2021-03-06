#pragma once

#include "../../Orbis/Components/Component.h"
#include "../../Orbis/Game/Entity.h"
using namespace orb;

namespace app
{
	// test the particle renderer component
	class ParticleSystemTester : public Component
	{
	public:
		// ctor
		ParticleSystemTester()
			: Component::Component(), m_currentTarget(TopTarget)
		{ }

		// override
		void update(); 

	private: 
		// the speed
		static float Speed;

		// the top target
		static Vector2f TopTarget;

		// the bottom target
		static Vector2f BottomTarget;

		// the currently set target
		Vector2f m_currentTarget;
	};
}