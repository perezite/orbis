#pragma once

#include "../../Orbis/Game/Level.h"
using namespace Game;

namespace Levels
{
	class LevelHelper
	{
	public:
		// add level switch buttons
		static void AddLevelSwitcher(Level* currentLevel, Level* targetLevel, bool isForward);
	};
}