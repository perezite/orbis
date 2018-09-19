#pragma once

#include "../../Orbis/Game/Level.h"
using namespace orb;

namespace app
{
	class Level8 : public Level
	{
	public:
		// override
		void start();

		void update();
	};
}