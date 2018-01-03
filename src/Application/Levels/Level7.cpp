#include "Level7.h"

#include "../Controllers/BallController.h"
using namespace Controllers;

#include "../../Orbis/Components/Camera.h"
#include "../../Orbis/Components/SpriteRenderer.h"
#include "../../Orbis/Video/VideoManager.h"
using namespace Components;
using namespace Video;

namespace Levels
{
	Level7::Level7()
	{
		// init camera
		Entity* cam = new Entity();
		cam->AddComponent(new Camera());
		AddEntity(cam);

		// init ball 
		Entity* ballEntity = new Entity();
		BallController* ballController = new BallController();
		BallEffectsController* ballEffectsController = new BallEffectsController();
		ballController->SetBallEffectsController(ballEffectsController);
		ballEntity->AddComponent(ballController);
		AddEntity(ballEntity);
	}
}
