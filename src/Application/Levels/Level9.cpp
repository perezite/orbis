#include "Level9.h"

#include "LevelUtil.h"
#include "Level8.h"
#include "Level10.h"

#include "../../Orbis/Orbis.h"
using namespace orb;

namespace app
{
	void Level9::start()
	{
		build()->entity()->withComponent(new Camera())->go();

		// add level switchers
		LevelUtil::addLevelSwitcher<Level8>(false);
		LevelUtil::addLevelSwitcher<Level10>(true);

		build()->entity()->withComponent(new SpriteRenderer("Textures/YellowBlock.png"))
			->withPosition(-0.25f, 0.3f)->withScale(0.33f, 0.33f)->go();

		build()->entity()->withComponent(new SpriteRenderer("Textures/YellowBlock.png"))
			->withPosition(0.25f, 0.3f)->withScale(0.33f, 0.33f)->go();

		build()->entity()->withComponent(new SpriteRenderer("Textures/RedBlock.png"))
			->withScale(0.33f, 0.33f)->go();

		build()->entity()->withComponent(new ParticleRenderer("Textures/GreenParticle.png"))
			->withPosition(0.0f, -0.3f)->withScale(0.1f, 0.1f)->go();
	}
}
