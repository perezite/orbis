#include "Level2.h"

#include "Level1.h"
#include "Level3.h"
#include "LevelHelper.h"

#include "../Controllers/CameraController.h"
#include "../Controllers/SpriteController.h"
#include "../Controllers/DebugLineTester.h"
#include "../Controllers/LevelSwitchButtonController.h"
using namespace Controllers;

#include "../../Orbis/Components/SpriteRenderer.h"
#include "../../Orbis/Components/RectangleRenderer.h"
#include "../../Orbis/Components/Camera.h"
#include "../../Orbis/Video/VideoManager.h"
#include "../../Orbis/Core/DebugHelper.h"
#include "../../Base/Math/Vector2D.h"
#include "../../Base/Math/MathHelper.h"
using namespace Components;
using namespace Core;
using namespace Math;
using namespace Video;

namespace Levels
{
	void Level2::start()
	{
		// textures
		Texture* coordSystemTexture = VideoManager::getInstance()->getTexture("Textures/CoordinateSystem.png");
		Texture* yellowBlockTexture = VideoManager::getInstance()->getTexture("Textures/YellowBlock.png");

		// camera entity
		Entity* camera = new Entity();
		Camera* cam = new Camera();
		camera->addComponent(cam);
		CameraController* cameraController = new CameraController();
		camera->addComponent(cameraController);
		this->addEntity(camera);

		// add level switchers
		LevelHelper::AddLevelSwitcher<Level1>(this, false);
		LevelHelper::AddLevelSwitcher<Level3>(this, true);

		// coordinate system entity
		Entity* coordSystem = new Entity("Coordinate System");
		coordSystem->addComponent(new SpriteRenderer(coordSystemTexture));
		this->addEntity(coordSystem);

		// yellow block entity
		Entity* yellowBlock = new Entity("Yellow Brick");
		yellowBlock->addComponent(new SpriteRenderer(yellowBlockTexture));
		yellowBlock->setTransform(Transform(Vector2D(0.25f, 0.3f), 0.0f, Vector2D(0.33f, 0.33f)));
		this->addEntity(yellowBlock);

		// red flat rect entity
		Entity* redFlatRect = new Entity("Red Flat Rect");
		redFlatRect->addComponent(new RectangleRenderer(Color(1.0f, 0.0f, 0.0f)));
		redFlatRect->setTransform(Transform(Vector2D(-0.2f, 0.3f), MathHelper::GetPi() / 7.0f, Vector2D(0.2f, 0.2f)));
		this->addEntity(redFlatRect);

		// green flat rect entity
		Entity* greenRect = new Entity("Green Flat Rect");
		greenRect->addComponent(new RectangleRenderer(Color(0.0f, 1.0f, 0.0f)));
		greenRect->setTransform(Transform(Vector2D(0.2f, -0.3f), 0.f, Vector2D(0.1f, 0.1f)));
		this->addEntity(greenRect);

		// line renderer
		ORBIS_DEBUG (
			Entity* debugLineEntity = new Entity("Debug Lines");
			debugLineEntity->addComponent(new DebugLineTester());
			this->addEntity(debugLineEntity);
		)
	}
}
