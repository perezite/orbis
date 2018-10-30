#include "Level3.h"

#include "Level2.h"
#include "Level4.h"
#include "LevelUtil.h"

#include "../Controllers/DebugLineTester.h"
#include "../Controllers/WobbleEffect.h"

#include "../../Base/Base.h"
using namespace base;

#include "../../Orbis/Orbis.h"
using namespace orb;

#include <iostream>

namespace app
{
	const int Level3::NUM_SPRITES = 1000;
	const float Level3::MIN_BLOCK_SCALE = 0.01f;
	const float Level3::MAX_BLOCK_SCALE = 0.05f;

	void Level3::start()
	{
		 // init textures
		std::vector<std::string> textures = { "Textures/BlackBlock.png", "Textures/BlueBlock.png", "Textures/CyanBlock.png",
			"Textures/GreenBlock.png", "Textures/GreyBlock.png", "Textures/OrangeBlock.png", "Textures/PurpleBlock.png", 
			"Textures/RedBlock.png", "Textures/VioletBlock.png", "Textures/YellowBlock.png" };

		VideoManager::instance()->getTextureAtlas()->add(textures);

		build()->entity("camera")->withComponent(new Camera())->go();

		// init blocks
		for (unsigned int i = 0; i < NUM_SPRITES; i++)
		{
			static int counter = 0;
			bool hasTexture = ++counter % 2 == 0;
			Component* renderer = hasTexture ? new SpriteRenderer(textures[rand() % textures.size()]) 
				: (Component*)new RectangleRenderer(Color(1.0f, 0.0f, 0.0f));

			build()->entity()->withComponent(renderer)
				->withComponent(new WobbleEffect())->withPosition(MathUtil::getRandom() - 0.5f, MathUtil::getRandom() - 0.5f)->go();
		}

		// add level switchers. Note: because we have no layering yet, the sprites above must be generated first in order to be batched in the right order
		LevelUtil::addLevelSwitcher<Level2>(false);
		LevelUtil::addLevelSwitcher<Level4>(true);

		// init debug line tester
		ORBIS_DEBUG(
			build()->entity("debugLineTester")->withComponent(new DebugLineTester())->go();
		);
	}
}
