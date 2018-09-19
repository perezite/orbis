#pragma once

#include "../../Orbis/Components/Component.h"
using namespace orb;

namespace app
{
	class WobbleEffect : public Component
	{
	public:
		// start
		void start();

		// update
		void update();

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