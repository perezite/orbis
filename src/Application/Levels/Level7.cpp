#include "Level7.h"

#include "LevelHelper.h"
#include "Level6.h"
#include "Level8.h"

#include "../Controllers/BallController.h"
using namespace Controllers;

#include "../../Orbis/Components/Camera.h"
#include "../../Orbis/Components/SpriteRenderer.h"
#include "../../Orbis/Video/VideoManager.h"
using namespace Components;
using namespace Video;

namespace Levels
{
	void Level7::Start()
	{
		// init camera
		Entity* cam = new Entity();
		cam->AddComponent(new Camera());
		AddEntity(cam);

		// add level switchers
		LevelHelper::AddLevelSwitcher(this, new Level6(), false);
		LevelHelper::AddLevelSwitcher(this, new Level8(), true);

		// init ball 
		Entity* ballEntity = new Entity();
		BallController* ballController = new BallController();
		BallEffectsController* ballEffectsController = new BallEffectsController();
		ballController->SetBallEffectsController(ballEffectsController);
		ballEntity->AddComponent(ballController);
		AddEntity(ballEntity);
	}
}
