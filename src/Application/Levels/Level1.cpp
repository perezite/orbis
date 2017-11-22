#include "Level1.h"

#include "../Controllers/CameraController.h"
#include "../Controllers/SpriteController.h"
using namespace Controllers;

#include "../../Orbis/Components/SpriteRenderer.h"
#include "../../Orbis/Components/Camera.h"
#include "../../Orbis/Video/VideoManager.h"
#include "../../Base/Math/Vector2D.h"
#include "../../Base/Math/MathHelper.h"
using namespace Components;
using namespace Math;
using namespace Video;

namespace Levels
{
	Level1::Level1()
	{
		// textures
		Texture* coordSystemTexture = new Texture("Textures/CoordinateSystem.png");
		Texture* yellowBlockTexture = new Texture("Textures/YellowBlock.png");
		Texture* blueBlockTexture = new Texture("Textures/BlueBlock.png");
		Texture* inputStateYellowBlockRotateLeft = new Texture("Textures/InputStateYellowBlockRotateLeft.png");
		Texture* inputStateYellowBlockRotateRight = new Texture("Textures/InputStateYellowBlockRotateRight.png");

		// camera entity
		Entity* camera = new Entity();
		camera->AddComponent(new Camera());
		camera->AddComponent(new CameraController());
		camera->SetTransform(Transform(Vector2D(-0.1f, -0.1f), 0.0f, Vector2D::One));
		this->AddEntity(camera);

		// coordinate system entity
		Entity* coordSystem = new Entity("Coordinate System");
		coordSystem->AddComponent(new SpriteRenderer(coordSystemTexture));
		this->AddEntity(coordSystem);

		// yellow block entity
		Entity* yellowBlock = new Entity("Yellow Brick");
		SpriteController* yellowBlockController = new SpriteController();
		yellowBlockController->SetOmega(MathHelper::GetPi());
		yellowBlock->AddComponent(yellowBlockController);
		yellowBlock->AddComponent(new SpriteRenderer(yellowBlockTexture));
		yellowBlock->SetTransform(Transform(Vector2D(0.25f, 0.1f), 0.0f, Vector2D(0.33f, 0.33f)));
		this->AddEntity(yellowBlock);

		// blue block entity
		Entity* blueBlock = new Entity("Blue Brick");
		SpriteController* blueBlockController = new SpriteController();
		blueBlockController->SetOmega(-MathHelper::GetPi() / 2.0f);
		blueBlock->AddComponent(blueBlockController);
		blueBlock->AddComponent(new SpriteRenderer(blueBlockTexture));
		blueBlock->SetTransform(Transform(Vector2D(-0.25f, -0.1f), 0.0f, Vector2D(0.15f, 0.15f)));
		this->AddEntity(blueBlock);

		// input mode display entity
		Entity* inputModeDisplay = new Entity("InputModeDisplay");
		inputModeDisplay->AddComponent(new SpriteRenderer(inputStateYellowBlockRotateLeft));
		inputModeDisplay->SetTransform(Transform(Vector2D(-0.25f, -0.25f), 0.0f, Vector2D(0.25f, 0.25f)));
		this->AddEntity(inputModeDisplay);
	}
}
