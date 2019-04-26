#include "Level7.h"

#include "LevelUtil.h"
#include "Level6.h"
#include "Level8.h"

#include "../Controllers/Ball.h"

#include "../../Orbis/Orbis.h"
using namespace orb;

namespace app
{
	void Level7::start()
	{
		build()->entity()->withComponent(new Camera())->go();

		// add level switchers
		LevelUtil::addLevelSwitcher<Level6>(false);
		LevelUtil::addLevelSwitcher<Level8>(true);

		// init ball
		build()->entity()->withComponent(new BallEffects())->withComponent(new Ball())->go();
	}
}
