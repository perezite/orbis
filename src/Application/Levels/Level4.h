#pragma once

#include "../../Orbis/Game/Level.h"
using namespace game;

namespace levels
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