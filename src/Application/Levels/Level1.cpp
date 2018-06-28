#include "Level1.h"

#include "Level2.h"
#include "LevelHelper.h"

#include "../Controllers/CameraController.h"
#include "../Controllers/SpriteController.h"
#include "../Controllers/InputModeButtonController.h"
#include "../Controllers/TransformButtonController.h"
#include "../Controllers/CloseButtonController.h"
#include "../Controllers/LevelSwitchButtonController.h"
using namespace controllers;

#include "../../Orbis/Components/SpriteRenderer.h"
#include "../../Orbis/Components/Camera.h"
#include "../../Orbis/Video/VideoManager.h"
#include "../../Base/Math/Vector2D.h"
#include "../../Base/Math/MathHelper.h"
using namespace components;
using namespace base::math;
using namespace video;

#include <map>

namespace levels
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
		camEntity->addComponent(cam);
		camEntity->addComponent(camController);
		camEntity->setTransform(Transform(Vector2D::Zero, 0.0f, Vector2D::One));
		this->addEntity(camEntity);

		// create level switcher
		LevelHelper::AddLevelSwitcher<Level2>(this, true);

		// coordinate system entity
		Entity* coordSystem = new Entity("Coordinate System");
		coordSystem->addComponent(new SpriteRenderer(coordSystemTexture));
		this->addEntity(coordSystem);

		// yellow block entity
		Entity* yellowBlock = new Entity("Yellow Brick");
		SpriteController* yellowBlockController = new SpriteController(MathHelper::getPi());
		yellowBlock->addComponent(yellowBlockController);
		yellowBlock->addComponent(new SpriteRenderer(yellowBlockTexture));
		yellowBlock->setTransform(Transform(Vector2D(0.25f, 0.1f), 0.0f, Vector2D(0.33f, 0.33f)));
		this->addEntity(yellowBlock);

		// blue block entity
		Entity* blueBlock = new Entity("Blue Brick");
		SpriteController* blueBlockController = new SpriteController(-MathHelper::getPi() / 2.0f);
		blueBlock->addComponent(blueBlockController);
		blueBlock->addComponent(new SpriteRenderer(blueBlockTexture));
		blueBlock->setTransform(Transform(Vector2D(-0.25f, -0.1f), 0.0f, Vector2D(0.15f, 0.15f)));
		this->addEntity(blueBlock);

		// input mode button
		Entity* inputModeButton = new Entity("input mode button");
		SpriteRenderer* inputModeButtonRenderer = new SpriteRenderer(rotateYellowSpriteTex);
		inputModeButton->addComponent(inputModeButtonRenderer);
		std::vector<Texture*> inputModeTextures = { rotateYellowSpriteTex, translateYellowSpriteTex, translateBlueSpriteTex, rotateCameraTex, translateCameraTex, scaleCameraTex, resetTex };
		inputModeButton->addComponent(new InputModeButtonController(inputModeButtonRenderer, inputModeTextures));
		inputModeButton->setTransform(Transform(Vector2D(-0.25f * cam->getSize().x, 0.25f * cam->getSize().y), 0.0f, Vector2D(0.25f, 0.25f), TransformSpace::Camera));
		this->addEntity(inputModeButton);

		// left button
		Entity* leftButton = new Entity("left button");
		leftButton->addComponent(new SpriteRenderer(leftArrowTex));
		leftButton->addComponent(new TransformButtonController(yellowBlockController, blueBlockController, camController, inputModeButtonRenderer, false));
		leftButton->setTransform(Transform(Vector2D(-0.25f, -0.25f * cam->getSize().y), 0.0f, Vector2D(0.5f, 0.5f), TransformSpace::Camera));
		this->addEntity(leftButton);

		// right button
		Entity* rightButton = new Entity("right button");
		rightButton->addComponent(new SpriteRenderer(rightArrowTex));
		rightButton->addComponent(new TransformButtonController(yellowBlockController, blueBlockController, camController, inputModeButtonRenderer, true));
		rightButton->setTransform(Transform(Vector2D(0.25f * cam->getSize().x, -0.25f * cam->getSize().y), 0.0f, Vector2D(0.5f, 0.5f), TransformSpace::Camera));
		this->addEntity(rightButton);

		// close button
		Entity* closeButton = new Entity("close button");
		closeButton->addComponent(new SpriteRenderer(closeTex));
		closeButton->addComponent(new CloseButtonController());
		closeButton->setTransform(Transform(Vector2D(0.25f * cam->getSize().x, 0.25f * cam->getSize().y), 0.0f, Vector2D(0.25f, 0.25f), TransformSpace::Camera));
		this->addEntity(closeButton);
	}
}
