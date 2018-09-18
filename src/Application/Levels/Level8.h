#pragma once

#include "../../Orbis/Game/Level.h"
using namespace orb::game;

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