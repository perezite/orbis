#pragma once

#include "../../Orbis/Game/Level.h"
using namespace Game;

namespace Levels
{
	class Level4 : public Level
	{
	public:
		// override
		void Start();

		// override
		void Release();

	private:
		// original window resolution
		Vector2D m_originalResolution;
	};
}