#pragma once

#include "../../Orbis/Game/Level.h"
using namespace orb::game;

#include <iostream>

namespace app
{
	class Level1 : public Level
	{
	public:		
		// override
		void start();
	};
}