#pragma once

#include "../../Orbis/Components/Component.h"
#include "../../Orbis/Game/Entity.h"
using namespace Components;
using namespace Game;

namespace Controllers
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
		void Update(); 

	private: 
		// the speed
		static float Speed;

		// the top target
		static Vector2D TopTarget;

		// the bottom target
		static Vector2D BottomTarget;

		// the currently set target
		Vector2D m_currentTarget;
	};
}