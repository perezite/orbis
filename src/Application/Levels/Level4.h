#pragma once

#include "../../Orbis/Game/Level.h"
using namespace Game;

namespace Levels
{
	class Level4 : public Level
	{
	public:
		// dtor
		~Level4();

		// override
		void start();

	private:
		// original window resolution
		Vector2D m_originalResolution;
	};
}