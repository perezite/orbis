#pragma once

#include "../../Orbis/Components/Component.h"
using namespace orbis::components;

namespace controllers
{
	class SpriteController : public Component
	{
	public:
		// ctor
		SpriteController(float omega) { m_omega = omega; }

		// get rotation velocity
		float getOmega() const { return m_omega; }

	public: 
		float m_omega; 
	};
}