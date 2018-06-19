#include "Level1.h"

#include "Level2.h"
#include "LevelHelper.h"

#include "../Controllers/CameraController.h"
#include "../Controllers/SpriteController.h"
#include "../Controllers/InputModeButtonController.h"
#include "../Controllers/TransformButtonController.h"
#include "../Controllers/CloseButtonController.h"
#include "../Controllers/LevelSwitchButtonController.h"
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
	void Level1::start()
	{
		// textures
		Texture* coordSystemTexture = VideoManager::getInstance()->getTexture("Textures/CoordinateSystem.png");
		Texture* yellowBlockTexture = VideoManager::getInstance()->getTexture("Textures/YellowBlock.png");
		Texture* blueBlockTexture = VideoManager::getInstance()->getTexture("Textures/BlueBlock.png");
		Texture* rotateYellowSpriteTex = VideoManager::getInstance()->getTexture("Textures/RotateYellowSprite.png");
		Texture* translateYellowSpriteTex = VideoManager::getInstance()->getTexture("Textures/TranslateYellowSprite.png");
		Texture* translateBlueSpriteTex = VideoManager::getInstance()->getTexture("Textures/TranslateBlueSprite.png");
		Texture* rotateCameraTex = VideoManager::getInstance()->getTexture("Textures/RotateCamera.png");
		Texture* translateCameraTex = VideoManager::getInstance()->getTexture("Textures/TranslateCamera.png");
		Texture* resetTex = VideoManager::getInstance()->getTexture("Textures/Reset.png");
		Texture* scaleCameraTex = VideoManager::getInstance()->getTexture("Textures/ScaleCamera.png");
		Texture* closeTex = VideoManager::getInstance()->getTexture("Textures/OverlayClose.png");
		Texture* leftArrowTex = VideoManager::getInstance()->getTexture("Textures/OverlayLeft.png");
		Texture* rightArrowTex = VideoManager::getInstance()->getTexture("Textures/OverlayRight.png");

		// camera entity
		Entity* camEntity = new Entity();
		Camera* cam = new Camera();
		CameraController* camController = new CameraController();
		camEntity->AddComponent(cam);
		camEntity->AddComponent(camController);
		camEntity->setTransform(Transform(Vector2D::Zero, 0.0f, Vector2D::One));
		this->AddEntity(camEntity);

		// create level switcher
		LevelHelper::AddLevelSwitcher<Level2>(this, true);

		// coordinate system entity
		Entity* coordSystem = new Entity("Coordinate System");
		coordSystem->AddComponent(new SpriteRenderer(coordSystemTexture));
		this->AddEntity(coordSystem);

		// yellow block entity
		Entity* yellowBlock = new Entity("Yellow Brick");
		SpriteController* yellowBlockController = new SpriteController(MathHelper::GetPi());
		yellowBlock->AddComponent(yellowBlockController);
		yellowBlock->AddComponent(new SpriteRenderer(yellowBlockTexture));
		yellowBlock->setTransform(Transform(Vector2D(0.25f, 0.1f), 0.0f, Vector2D(0.33f, 0.33f)));
		this->AddEntity(yellowBlock);

		// blue block entity
		Entity* blueBlock = new Entity("Blue Brick");
		SpriteController* blueBlockController = new SpriteController(-MathHelper::GetPi() / 2.0f);
		blueBlock->AddComponent(blueBlockController);
		blueBlock->AddComponent(new SpriteRenderer(blueBlockTexture));
		blueBlock->setTransform(Transform(Vector2D(-0.25f, -0.1f), 0.0f, Vector2D(0.15f, 0.15f)));
		this->AddEntity(blueBlock);

		// input mode button
		Entity* inputModeButton = new Entity("input mode button");
		SpriteRenderer* inputModeButtonRenderer = new SpriteRenderer(rotateYellowSpriteTex);
		inputModeButton->AddComponent(inputModeButtonRenderer);
		std::vector<Texture*> inputModeTextures = { rotateYellowSpriteTex, translateYellowSpriteTex, translateBlueSpriteTex, rotateCameraTex, translateCameraTex, scaleCameraTex, resetTex };
		inputModeButton->AddComponent(new InputModeButtonController(inputModeButtonRenderer, inputModeTextures));
		inputModeButton->setTransform(Transform(Vector2D(-0.25f * cam->getCount().x, 0.25f * cam->getCount().y), 0.0f, Vector2D(0.25f, 0.25f), TransformSpace::Camera));
		this->AddEntity(inputModeButton);

		// left button
		Entity* leftButton = new Entity("left button");
		leftButton->AddComponent(new SpriteRenderer(leftArrowTex));
		leftButton->AddComponent(new TransformButtonController(yellowBlockController, blueBlockController, camController, inputModeButtonRenderer, false));
		leftButton->setTransform(Transform(Vector2D(-0.25f, -0.25f * cam->getCount().y), 0.0f, Vector2D(0.5f, 0.5f), TransformSpace::Camera));
		this->AddEntity(leftButton);

		// right button
		Entity* rightButton = new Entity("right button");
		rightButton->AddComponent(new SpriteRenderer(rightArrowTex));
		rightButton->AddComponent(new TransformButtonController(yellowBlockController, blueBlockController, camController, inputModeButtonRenderer, true));
		rightButton->setTransform(Transform(Vector2D(0.25f * cam->getCount().x, -0.25f * cam->getCount().y), 0.0f, Vector2D(0.5f, 0.5f), TransformSpace::Camera));
		this->AddEntity(rightButton);

		// close button
		Entity* closeButton = new Entity("close button");
		closeButton->AddComponent(new SpriteRenderer(closeTex));
		closeButton->AddComponent(new CloseButtonController());
		closeButton->setTransform(Transform(Vector2D(0.25f * cam->getCount().x, 0.25f * cam->getCount().y), 0.0f, Vector2D(0.25f, 0.25f), TransformSpace::Camera));
		this->AddEntity(closeButton);
	}
}
