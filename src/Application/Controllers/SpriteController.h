#pragma once

#include "../../Orbis/Components/Component.h"
using namespace Components;

namespace Controllers
{
	class SpriteController : public Component
	{
	public:
		// set rotation velocity
		void SetOmega(float omega) { m_omega = omega; }

		// get rotation velocity
		float GetOmega() const { return m_omega; }

	public: 
		float m_omega; 
	};
}