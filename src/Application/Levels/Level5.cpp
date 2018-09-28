#include "Level5.h"

#include "LevelUtil.h"
#include "Level4.h"
#include "Level6.h"

#include "../../Orbis/Orbis.h"
using namespace orb;

namespace app
{
	void Level5::start()
	{
		build()->entity()->withComponent(new Camera())->go();

		LevelUtil::addLevelSwitcher<Level4>(false);
		LevelUtil::addLevelSwitcher<Level6>(true);

		build()->entity("yellowBrick")->withComponent(new SpriteRenderer("Textures/YellowBlock.png"))
			->withPosition(-0.25f, 0.3f)->withScale(0.33f, 0.33f)->go();

		build()->entity("redBrick")->withComponent(new SpriteRenderer("Textures/RedBlock.png"))
			->withScale(0.33f, 0.33f)->go();

		build()->entity("greenBrick")->withComponent(new SpriteRenderer("Textures/GreenBlock.png"))
			->withPosition(0.25f, 0.3f)->withScale(0.33f, 0.33f)->go();
	}
}
