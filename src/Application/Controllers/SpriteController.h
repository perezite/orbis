#pragma once

#include "../../Orbis/Components/Component.h"
using namespace Components;

namespace Controllers
{
	class SpriteController : public Component
	{
	public:
		void Update();

		void SetOmega(float omega) { m_omega = omega; }

	public: 
		float m_omega; 
	};
}