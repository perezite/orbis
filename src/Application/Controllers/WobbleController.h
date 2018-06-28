#pragma once

#include "../../Orbis/Components/Component.h"
using namespace components;

namespace controllers
{
	class WobbleController : public Component
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