#include "Level2.h"

#include "Level1.h"
#include "Level3.h"
#include "LevelUtil.h"

#include "../Controllers/CameraBehavior.h"
#include "../Controllers/SpriteController.h"
#include "../Controllers/DebugLineTester.h"
#include "../Controllers/LevelSwitchButtonController.h"

#include "../../Orbis/Orbis.h"
using namespace orb;

namespace app
{
	void Level2::start()
	{
		build()->entity()->withComponent(new Camera())->withComponent(new CameraBehavior())->go();

		 LevelUtil::addLevelSwitcher<Level1>(false);
		 LevelUtil::addLevelSwitcher<Level3>(true);

		build()->entity("coordinateSystem")->withComponent(new SpriteRenderer("Textures/CoordinateSystem.png"))->go();

		build()->entity("yellowBrick")->withComponent(new SpriteRenderer("Textures/YellowBlock.png"))
			->withPosition(0.25f, 0.3f)->withScale(0.33f, 0.33f)->go();

		build()->entity("redFlatRect")->withComponent(new RectangleRenderer(Color(1.0f, 0.0f, 0.0f)))
			->withPosition(-0.2f, 0.3f)->withRotation(MathUtil::getPi() / 7.0f)->withScale(0.2f, 0.2f)->go();

		build()->entity("greenFlatRect")->withComponent(new RectangleRenderer(Color(0.0f, 1.0f, 0.0f)))
			->withPosition(0.2f, -0.3f)->withScale(0.1f, 0.1f)->go();

		ORBIS_DEBUG(
			build()->entity("debugLines")->withComponent(new DebugLineTester())->go();
		)
	}
}
