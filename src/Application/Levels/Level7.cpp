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
		// init camera
		Entity* cam = new Entity();
		cam->addComponent(new Camera());
		addEntity(cam);

		// add level switchers
		LevelUtil::addLevelSwitcher<Level6>(false);
		LevelUtil::addLevelSwitcher<Level8>(true);

		// init ball 
		Entity* ballEntity = new Entity();
		Ball* ballController = new Ball();
		BallEffects* ballEffectsController = new BallEffects();
		ballController->setBallEffectsController(ballEffectsController);
		ballEntity->addComponent(ballController);
		addEntity(ballEntity);
	}
}
