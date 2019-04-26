#include "Level6.h"

#include "LevelUtil.h"
#include "Level5.h"
#include "Level7.h"

#include "../../Orbis/Orbis.h"
using namespace orb;

namespace app
{
	void Level6::start()
	{
		build()->entity()->withComponent(new Camera())->go();

		LevelUtil::addLevelSwitcher<Level5>(false);
		LevelUtil::addLevelSwitcher<Level7>(true);

		build()->entity()->withComponent(new SpriteRenderer("Textures/BleedingTestBlue.png"))
			->withPosition(-0.25f, -0.25f)->withScale(0.33f, 0.33f)->go();

		build()->entity()->withComponent(new SpriteRenderer("Textures/BleedingTestGreen.png"))
			->withPosition( 0.25f, -0.25f)->withScale(0.33f, 0.33f)->go();

		build()->entity()->withComponent(new SpriteRenderer("Textures/BleedingTestRed.png"))
			->withPosition( 0.25f, 0.25f)->withScale(0.33f, 0.33f)->go();

		build()->entity()->withComponent(new SpriteRenderer("Textures/BleedingTestYellow.png"))
			->withPosition(-0.25f, 0.25f)->withScale(0.33f, 0.33f)->go();
	}
}
