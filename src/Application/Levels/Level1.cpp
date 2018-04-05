#include "Level1.h"

#include "../Controllers/CameraController.h"
#include "../Controllers/SpriteController.h"
#include "../Controllers/InputModeButtonController.h"
#include "../Controllers/TransformButtonController.h"
using namespace Controllers;

#include "../../Orbis/Components/SpriteRenderer.h"
#include "../../Orbis/Components/Camera.h"
#include "../../Orbis/Video/VideoManager.h"
#include "../../Base/Math/Vector2D.h"
#include "../../Base/Math/MathHelper.h"
using namespace Components;
using namespace Math;
using namespace Video;

#include <map>

namespace Levels
{
	Level1::Level1()
	{
		// textures
		Texture* coordSystemTexture = new Texture("Textures/CoordinateSystem.png");
		Texture* yellowBlockTexture = new Texture("Textures/YellowBlock.png");
		Texture* blueBlockTexture = new Texture("Textures/BlueBlock.png");
		Texture* rotateYellowSpriteTex = new Texture("Textures/RotateYellowSprite.png");
		Texture* translateYellowSpriteTex = new Texture("Textures/TranslateYellowSprite.png");
		Texture* translateBlueSpriteTex = new Texture("Textures/TranslateBlueSprite.png");
		Texture* rotateCameraTex = new Texture("Textures/RotateCamera.png");
		Texture* translateCameraTex = new Texture("Textures/TranslateCamera.png");
		Texture* resetTex = new Texture("Textures/Reset.png");
		Texture* scaleCameraTex = new Texture("Textures/ScaleCamera.png");
		Texture* leftArrowTex = new Texture("Textures/OverlayLeft.png");
		Texture* rightArrowTex = new Texture("Textures/OverlayRight.png");
		Texture* closeTex = new Texture("Textures/OverlayClose.png");

		// camera entity
		Entity* camEntity = new Entity();
		Camera* cam = new Camera();
		CameraController* camController = new CameraController();
		camEntity->AddComponent(cam);
		camEntity->AddComponent(camController);
		camEntity->SetTransform(Transform(Vector2D::Zero, 0.0f, Vector2D::One));
		this->AddEntity(camEntity);

		/*
		// previous level button entity
		Entity* prevLevel = new Entity("Previous level");
		prevLevel->AddComponent(new SpriteRenderer(leftArrowTex));
		prevLevel->SetTransform(Transform(Vector2D(-0.45f * cam->GetSize().x, 0.45f * cam->GetSize().y), 0.0f, Vector2D(0.1f, 0.1f), TransformSpace::CameraSpace));
		this->AddEntity(prevLevel);

		// next level button entity
		Entity* nextLevel = new Entity("Next level");
		nextLevel->AddComponent(new SpriteRenderer(rightArrowTex));
		nextLevel->SetTransform(Transform(Vector2D(0.45f * cam->GetSize().x, 0.45f * cam->GetSize().y), 0.0f, Vector2D(0.1f, 0.1f), TransformSpace::CameraSpace));
		this->AddEntity(nextLevel);*/

		// coordinate system entity
		Entity* coordSystem = new Entity("Coordinate System");
		coordSystem->AddComponent(new SpriteRenderer(coordSystemTexture));
		this->AddEntity(coordSystem);

		// yellow block entity
		Entity* yellowBlock = new Entity("Yellow Brick");
		SpriteController* yellowBlockController = new SpriteController(MathHelper::GetPi());
		yellowBlock->AddComponent(yellowBlockController);
		yellowBlock->AddComponent(new SpriteRenderer(yellowBlockTexture));
		yellowBlock->SetTransform(Transform(Vector2D(0.25f, 0.1f), 0.0f, Vector2D(0.33f, 0.33f)));
		this->AddEntity(yellowBlock);

		// blue block entity
		Entity* blueBlock = new Entity("Blue Brick");
		SpriteController* blueBlockController = new SpriteController(-MathHelper::GetPi() / 2.0f);
		blueBlock->AddComponent(blueBlockController);
		blueBlock->AddComponent(new SpriteRenderer(blueBlockTexture));
		blueBlock->SetTransform(Transform(Vector2D(-0.25f, -0.1f), 0.0f, Vector2D(0.15f, 0.15f)));
		this->AddEntity(blueBlock);

		// input mode button
		Entity* inputModeButton = new Entity("input mode button");
		SpriteRenderer* inputModeButtonRenderer = new SpriteRenderer(rotateYellowSpriteTex);
		inputModeButton->AddComponent(inputModeButtonRenderer);
		std::vector<Texture*> inputModeTextures = { rotateYellowSpriteTex, translateYellowSpriteTex, translateBlueSpriteTex, rotateCameraTex, translateCameraTex, scaleCameraTex, resetTex };
		inputModeButton->AddComponent(new InputModeButtonController(inputModeButtonRenderer, inputModeTextures));
		inputModeButton->SetTransform(Transform(Vector2D(-0.25f * cam->GetSize().x, 0.25f * cam->GetSize().y), 0.0f, Vector2D(0.25f, 0.25f), TransformSpace::CameraSpace));
		this->AddEntity(inputModeButton);

		// left button
		Entity* leftButton = new Entity("left button");
		SpriteRenderer* leftButtonRenderer = new SpriteRenderer(leftArrowTex);
		leftButton->AddComponent(leftButtonRenderer);
		leftButton->AddComponent(new TransformButtonController(leftButtonRenderer, yellowBlockController, blueBlockController, camController, inputModeButtonRenderer, false));
		leftButton->SetTransform(Transform(Vector2D(-0.25f, -0.25f * cam->GetSize().y), 0.0f, Vector2D(0.5f, 0.5f), TransformSpace::CameraSpace));
		this->AddEntity(leftButton);

		// right button
		Entity* rightButton = new Entity("right button");
		SpriteRenderer* rightButtonRenderer = new SpriteRenderer(rightArrowTex);
		rightButton->AddComponent(rightButtonRenderer);
		rightButton->AddComponent(new TransformButtonController(rightButtonRenderer, yellowBlockController, blueBlockController, camController, inputModeButtonRenderer, true));
		rightButton->SetTransform(Transform(Vector2D(0.25f * cam->GetSize().x, -0.25f * cam->GetSize().y), 0.0f, Vector2D(0.5f, 0.5f), TransformSpace::CameraSpace));
		this->AddEntity(rightButton);

		// close button
		Entity* closeButton = new Entity("close button");
		closeButton->AddComponent(new SpriteRenderer(closeTex));
		closeButton->SetTransform(Transform(Vector2D(0.25f * cam->GetSize().x, 0.25f * cam->GetSize().y), 0.0f, Vector2D(0.25f, 0.25f), TransformSpace::CameraSpace));
		this->AddEntity(closeButton);
	}
}
