#pragma once

#include "../../Orbis/Components/Component.h"
using namespace Components;

namespace Controllers
{
	class WobbleController : public Component
	{
	public:
		// start
		void Start();

		// update
		void Update();

	private:
		// is the entity currently growing
		bool m_isGrowing;

	private:
		// minimal scale
		static const float MIN_SCALE;

		// maximal scale
		static const float MAX_SCALE;
	};
}