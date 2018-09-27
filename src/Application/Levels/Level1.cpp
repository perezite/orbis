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
			m_entity = new Entity(name);
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
		std::vector<std::string> inputModeTextures = { 
			"Textures/RotateYellowSprite.png", "Textures/TranslateYellowSprite.png", "Textures/TranslateBlueSprite.png", 
			"Textures/RotateCamera.png", "Textures/TranslateCamera.png", "Textures/ScaleCamera.png", "Textures/Reset.png" };

		VideoManager::getInstance()->getTextureAtlas()->add(inputModeTextures);

		build(this)->entity()->withComponent(new Camera())->withComponent(new CameraBehavior())->go();

		build(this)->levelSwitcher<Level2>(true)->go();

		build(this)->entity("coordinate system")->withComponent(new SpriteRenderer("Textures/CoordinateSystem.png"))->go();

		build(this)->entity("yellowBlock")->withComponent(new SpriteRenderer("Textures/YellowBlock.png"))
			->withComponent(new SpriteController(MathUtil::getPi()))
			->withTransform(Transform(Vector2D(0.25f, 0.1f), 0.0f, Vector2D(0.33f, 0.33f)))->go();
		
		build(this)->entity("blueBlock")->withComponent(new SpriteRenderer("Textures/BlueBlock.png"))
			->withComponent(new SpriteController(-MathUtil::getPi() / 2.0f))
			->withTransform(Transform(Vector2D(-0.25f, -0.1f), 0.0f, Vector2D(0.15f, 0.15f)))->go();

		build(this)->entity("inputModeButton")->withComponent(new SpriteRenderer("Textures/RotateYellowSprite.png"))
			->withComponent(new InputModeButton(inputModeTextures))
			->withTransform(Transform(Vector2D(-0.25f * Camera::getInstance()->getSize().x, 0.25f * Camera::getInstance()->getSize().y), 0.0f, Vector2D(0.25f, 0.25f), TransformSpace::Camera))
			->go();

		build(this)->entity("leftButton")->withComponent(new SpriteRenderer("Textures/OverlayLeft.png"))
			->withComponent(new TransformButton(false))
			->withTransform(Transform(Vector2D(-0.25f * Camera::getInstance()->getSize().x, -0.25f * Camera::getInstance()->getSize().y), 0.0f, Vector2D(0.5f, 0.5f), TransformSpace::Camera))
			->go();

		build(this)->entity("rightButton")->withComponent(new SpriteRenderer("Textures/OverlayRight.png"))
			->withComponent(new TransformButton(true))
			->withTransform(Transform(Vector2D(0.25f * Camera::getInstance()->getSize().x, -0.25f * Camera::getInstance()->getSize().y), 0.0f, Vector2D(0.5f, 0.5f), TransformSpace::Camera))
			->go();

		build(this)->entity("closeButton")->withComponent(new SpriteRenderer("Textures/OverlayClose.png"))
			->withComponent(new CloseButton())
			->withTransform(Transform(Vector2D(0.25f * Camera::getInstance()->getSize().x, 0.25f * Camera::getInstance()->getSize().y), 0.0f, Vector2D(0.25f, 0.25f), TransformSpace::Camera))
			->go();
	}
}
