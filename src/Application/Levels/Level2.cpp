#include "Level2.h"

#include "Level1.h"
#include "Level3.h"

#include "../Controllers/CameraController.h"
#include "../Controllers/SpriteController.h"
#include "../Controllers/DebugLineTester.h"
#include "../Controllers/LevelSwitchButtonController.h"
using namespace Controllers;

#include "../../Orbis/Components/SpriteRenderer.h"
#include "../../Orbis/Components/RectangleRenderer.h"
#include "../../Orbis/Components/Camera.h"
#include "../../Orbis/Video/VideoManager.h"
#include "../../Base/Math/Vector2D.h"
#include "../../Base/Math/MathHelper.h"
using namespace Components;
using namespace Math;
using namespace Video;

namespace Levels
{
	void Level2::Start()
	{
		// textures
		Texture* coordSystemTexture = new Texture(this, "Textures/CoordinateSystem.png");
		Texture* yellowBlockTexture = new Texture(this, "Textures/YellowBlock.png");
		Texture* leftArrowTex = new Texture(this, "Textures/OverlayLeft.png");
		Texture* rightArrowTex = new Texture(this, "Textures/OverlayRight.png");

		// camera entity
		Entity* camera = new Entity();
		Camera* cam = new Camera();
		camera->AddComponent(cam);
		CameraController* cameraController = new CameraController();
		camera->AddComponent(cameraController);
		this->AddEntity(camera);

		// previous level button entity
		Entity* prevLevel = new Entity("Previous level Button");
		prevLevel->AddComponent(new SpriteRenderer(leftArrowTex));
		prevLevel->AddComponent(new LevelSwitchButtonController(new Level1()));
		prevLevel->SetTransform(Transform(Vector2D(-0.45f * cam->GetSize().x, 0.45f * cam->GetSize().y), 0.0f, Vector2D(0.1f, 0.1f), TransformSpace::CameraSpace));
		this->AddEntity(prevLevel);

		// next level button entity
		Entity* nextLevel = new Entity("Next level Button");
		nextLevel->AddComponent(new SpriteRenderer(rightArrowTex));
		nextLevel->AddComponent(new LevelSwitchButtonController(new Level3()));
		nextLevel->SetTransform(Transform(Vector2D(0.45f * cam->GetSize().x, 0.45f * cam->GetSize().y), 0.0f, Vector2D(0.1f, 0.1f), TransformSpace::CameraSpace));
		this->AddEntity(nextLevel);

		// coordinate system entity
		Entity* coordSystem = new Entity("Coordinate System");
		coordSystem->AddComponent(new SpriteRenderer(coordSystemTexture));
		this->AddEntity(coordSystem);

		// yellow block entity
		Entity* yellowBlock = new Entity("Yellow Brick");
		yellowBlock->AddComponent(new SpriteRenderer(yellowBlockTexture));
		yellowBlock->SetTransform(Transform(Vector2D(0.25f, 0.3f), 0.0f, Vector2D(0.33f, 0.33f)));
		this->AddEntity(yellowBlock);

		// red flat rect entity
		Entity* redFlatRect = new Entity("Red Flat Rect");
		redFlatRect->AddComponent(new RectangleRenderer(Color(1.0f, 0.0f, 0.0f)));
		redFlatRect->SetTransform(Transform(Vector2D(-0.2f, 0.3f), MathHelper::GetPi() / 7.0f, Vector2D(0.2f, 0.2f)));
		this->AddEntity(redFlatRect);

		// green flat rect entity
		Entity* greenRect = new Entity("Green Flat Rect");
		greenRect->AddComponent(new RectangleRenderer(Color(0.0f, 1.0f, 0.0f)));
		greenRect->SetTransform(Transform(Vector2D(0.2f, -0.3f), 0.f, Vector2D(0.1f, 0.1f)));
		this->AddEntity(greenRect);

		// line renderer
		Entity* debugLineEntity = new Entity("Debug Lines");
		debugLineEntity->AddComponent(new DebugLineTester());
		this->AddEntity(debugLineEntity);
	}
}
