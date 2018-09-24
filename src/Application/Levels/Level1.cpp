#include "Level1.h"

#include "Level2.h"
#include "LevelUtil.h"

#include "../Controllers/CameraBehavior.h"
#include "../Controllers/SpriteController.h"
#include "../Controllers/InputModeButton.h"
#include "../Controllers/TransformButton.h"
#include "../Controllers/CloseButton.h"
#include "../Controllers/LevelSwitchButtonController.h"

#include "../../Orbis/Orbis.h"
using namespace orb;

#include <map>
#include <vector>

namespace 
{
	using namespace app;

	class LevelBuilder
	{
	public:
		LevelBuilder()
		{
			reset();
		}

		void setLevel(Level* level) { m_level = level; }


		LevelBuilder* entity(std::string name = "")
		{
			m_entity = new Entity();
			return this;
		}

		LevelBuilder* withComponent(Component* component)
		{
			m_components.push_back(component);
			return this;
		}

		LevelBuilder* withTransform(Transform transform)
		{
			m_transform = transform;
			m_hasTransform = true;
			return this;
		}

		template <class T>
		LevelBuilder* levelSwitcher(bool isForward)
		{
			VideoManager* video = VideoManager::getInstance();

			Camera* cam = Camera::getInstance();
			float horzPos = isForward ? 0.45f * cam->getSize().x : -0.45f * cam->getSize().x;
			std::string texPath = isForward ? "Textures/OverlayRight.png" : "Textures/OverlayLeft.png";

			Entity* switcher = new Entity(isForward ? "next level Button" : "previous level Button");
			switcher->addComponent(new SpriteRenderer(texPath));
			switcher->addComponent(new LevelSwitchButtonController<T>(isForward));
			switcher->setTransform(Transform(Vector2D(horzPos, 0.45f * cam->getSize().y), 0.0f, Vector2D(0.1f, 0.1f), TransformSpace::Camera));
			m_entity = switcher;

			return this;
		}

		void go()
		{
			for (unsigned int i = 0; i < m_components.size(); i++)
				m_entity->addComponent(m_components[i]);

			if (m_hasTransform)
				m_entity->setTransform(m_transform);

			m_level->addEntity(m_entity);

			reset();
		}

	protected:
		void reset()
		{
			m_level = NULL;
			m_entity = NULL;
			m_transform = Transform(Vector2D::Zero, 0.0f, Vector2D::One);
			m_hasTransform = false;
			m_components.clear();
		}

	private:
		Level* m_level;

		Entity* m_entity;

		Transform m_transform;

		bool m_hasTransform;

		std::vector<Component*> m_components;
	};

	LevelBuilder builder;

	LevelBuilder* build(Level* level)
	{
		builder.setLevel(level);
		return &builder;
	}
}

namespace app
{
	void Level1::start()
	{
		build(this)->entity()->withComponent(new Camera())->withComponent(new CameraBehavior())
			->withTransform(Transform(Vector2D::Zero, 0.0f, Vector2D::One))->go();

		build(this)->entity("coordinate system")->withComponent(new SpriteRenderer("Textures/CoordinateSystem.png"))->go();

		build(this)->levelSwitcher<Level2>(true)->go();
	}

	/*void Level1::start()
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
		CameraBehavior* camController = new CameraBehavior();
		camEntity->addComponent(cam);
		camEntity->addComponent(camController);
		camEntity->setTransform(Transform(Vector2D::Zero, 0.0f, Vector2D::One));
		this->addEntity(camEntity);

		// create level switcher
		LevelUtil::AddLevelSwitcher<Level2>(this, true);

		// coordinate system entity
		Entity* coordSystem = new Entity("Coordinate System");
		coordSystem->addComponent(new SpriteRenderer(coordSystemTexture));
		this->addEntity(coordSystem);

		// yellow block entity
		Entity* yellowBlock = new Entity("Yellow Brick");
		SpriteController* yellowBlockController = new SpriteController(MathUtil::getPi());
		yellowBlock->addComponent(yellowBlockController);
		yellowBlock->addComponent(new SpriteRenderer(yellowBlockTexture));
		yellowBlock->setTransform(Transform(Vector2D(0.25f, 0.1f), 0.0f, Vector2D(0.33f, 0.33f)));
		this->addEntity(yellowBlock);

		// blue block entity
		Entity* blueBlock = new Entity("Blue Brick");
		SpriteController* blueBlockController = new SpriteController(-MathUtil::getPi() / 2.0f);
		blueBlock->addComponent(blueBlockController);
		blueBlock->addComponent(new SpriteRenderer(blueBlockTexture));
		blueBlock->setTransform(Transform(Vector2D(-0.25f, -0.1f), 0.0f, Vector2D(0.15f, 0.15f)));
		this->addEntity(blueBlock);

		// input mode button
		Entity* inputModeButton = new Entity("input mode button");
		SpriteRenderer* inputModeButtonRenderer = new SpriteRenderer(rotateYellowSpriteTex);
		inputModeButton->addComponent(inputModeButtonRenderer);
		std::vector<Texture*> inputModeTextures = { rotateYellowSpriteTex, translateYellowSpriteTex, translateBlueSpriteTex, rotateCameraTex, translateCameraTex, scaleCameraTex, resetTex };
		inputModeButton->addComponent(new InputModeButton(inputModeButtonRenderer, inputModeTextures));
		inputModeButton->setTransform(Transform(Vector2D(-0.25f * cam->getSize().x, 0.25f * cam->getSize().y), 0.0f, Vector2D(0.25f, 0.25f), TransformSpace::Camera));
		this->addEntity(inputModeButton);

		// left button
		Entity* leftButton = new Entity("left button");
		leftButton->addComponent(new SpriteRenderer(leftArrowTex));
		leftButton->addComponent(new TransformButton(yellowBlockController, blueBlockController, camController, inputModeButtonRenderer, false));
		leftButton->setTransform(Transform(Vector2D(-0.25f, -0.25f * cam->getSize().y), 0.0f, Vector2D(0.5f, 0.5f), TransformSpace::Camera));
		this->addEntity(leftButton);

		// right button
		Entity* rightButton = new Entity("right button");
		rightButton->addComponent(new SpriteRenderer(rightArrowTex));
		rightButton->addComponent(new TransformButton(yellowBlockController, blueBlockController, camController, inputModeButtonRenderer, true));
		rightButton->setTransform(Transform(Vector2D(0.25f * cam->getSize().x, -0.25f * cam->getSize().y), 0.0f, Vector2D(0.5f, 0.5f), TransformSpace::Camera));
		this->addEntity(rightButton);

		// close button
		Entity* closeButton = new Entity("close button");
		closeButton->addComponent(new SpriteRenderer(closeTex));
		closeButton->addComponent(new CloseButton());
		closeButton->setTransform(Transform(Vector2D(0.25f * cam->getSize().x, 0.25f * cam->getSize().y), 0.0f, Vector2D(0.25f, 0.25f), TransformSpace::Camera));
		this->addEntity(closeButton);
	}*/

}
