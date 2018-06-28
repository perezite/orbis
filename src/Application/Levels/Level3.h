#pragma once

#include "../../Orbis/Game/Level.h"
using namespace orbis::game;

#include <iostream>

namespace levels
{
	class Level3 : public Level
	{
	public:
		// override
		void start();

	private:
		static const int NUM_SPRITES;
		static const float MIN_BLOCK_SCALE;
		static const float MAX_BLOCK_SCALE;
	};
}