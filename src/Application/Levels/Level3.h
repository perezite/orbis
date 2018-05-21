#pragma once

#include "../../Orbis/Game/Level.h"
using namespace Game;

namespace Levels
{
	class Level3 : public Level
	{
	public:
		// override
		void Start();

	private:
		static const int NUM_SPRITES;
		static const float MIN_BLOCK_SCALE;
		static const float MAX_BLOCK_SCALE;
	};
}