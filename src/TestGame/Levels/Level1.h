#pragma once

#include "..\..\Orbis\Game\Level.h"
using namespace Game;

#include "..\..\Orbis\Video\Texture.h"
using namespace Video;

namespace Levels
{
	class Level1 : public Level
	{
	public:
		Level1();

		~Level1();

	private:
		Texture *m_texture;
	};
}