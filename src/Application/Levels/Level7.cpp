#include "Level7.h"

#include "LevelHelper.h"
#include "Level6.h"
#include "Level8.h"

#include "../Controllers/BallController.h"
using namespace controllers;

#include "../../Orbis/Components/Camera.h"
#include "../../Orbis/Components/SpriteRenderer.h"
#include "../../Orbis/Video/VideoManager.h"
using namespace orbis::components;
using namespace video;

namespace levels
{
	void Level7::start()
	{
		// init camera
		Entity* cam = new Entity();
		cam->addComponent(new Camera());
		addEntity(cam);

		// add level switchers
		LevelHelper::AddLevelSwitcher<Level6>(this, false);
		LevelHelper::AddLevelSwitcher<Level8>(this, true);

		// init ball 
		Entity* ballEntity = new Entity();
		BallController* ballController = new BallController();
		BallEffectsController* ballEffectsController = new BallEffectsController();
		ballController->setBallEffectsController(ballEffectsController);
		ballEntity->addComponent(ballController);
		addEntity(ballEntity);
	}
}
