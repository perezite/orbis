#include "Level10.h"

#include "LevelUtil.h"
#include "Level9.h"

#include "../../Orbis/Orbis.h"
using namespace orb;

namespace app
{
	void Level10::start()
	{
		build()->entity()->withComponent(new Camera())->go();

		LevelUtil::addLevelSwitcher<Level9>(false);

		build()->entity()->withComponent(new SimpleParticleRenderer("Textures/GreenParticle.png"))->go();
	}
}
