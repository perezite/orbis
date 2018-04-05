#include "Level2.h"

#include "../Controllers/CameraController.h"
#include "../Controllers/SpriteController.h"
#include "../Controllers/DebugLineTester.h"
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
	Level2::Level2()
	{
		// textures
		Texture* coordSystemTexture = new Texture("Textures/CoordinateSystem.png");
		Texture* yellowBlockTexture = new Texture("Textures/YellowBlock.png");

		// camera entity
		Entity* camera = new Entity();
		camera->AddComponent(new Camera());
		CameraController* cameraController = new CameraController();
		camera->AddComponent(cameraController);
		this->AddEntity(camera);

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
