#include "Level8.h"

#include "LevelUtil.h"
#include "Level7.h"
#include "Level9.h"

#include "../Controllers/WobbleBrickEffect.h"

#include "../../Orbis/Orbis.h"
using namespace orb;

namespace app
{
	void Level8::start()
	{
		build()->entity()->withComponent(new Camera())->go();

		LevelUtil::addLevelSwitcher<Level7>(false);
		LevelUtil::addLevelSwitcher<Level9>(true);

		build()->entity()->withComponent(new SpriteRenderer("Textures/YellowBlock.png"))
			->withComponent(new WobbleBrickEffect("Tweens/Test1.tween", 10.0f))->go();
	}
}
