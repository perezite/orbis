#include "TransformButton.h"

#include "../../Base/Base.h"
using namespace base;

#include "../../Orbis/Orbis.h"
using namespace orb;

namespace 
{
	using namespace app;

	void Rotate(Transform* transform, bool clockwise, float omega)
	{
		omega = clockwise ? -omega : omega;
		float alpha = transform->rotation;
		transform->rotation = alpha + TimeManager::instance()->getDeltaSeconds() * omega;
	}

	void Translate(Transform* transform, bool forward, float speed)
	{
		speed = forward ? speed : -speed;
		Vector2f position = transform->position;
		Vector2f translation = Matrix3::rotation2D(transform->rotation) * Vector2f(TimeManager::instance()->getDeltaSeconds() * speed, 0.0f);
		transform->position = position + translation;
	}

	void Scale(CameraBehavior *camera, bool positive)
	{
		float dt = TimeManager::instance()->getDeltaSeconds();
		float factor = positive ? 1 - dt * 0.5f : 1 + dt * 0.5f;
		Transform* transform = camera->getParent()->getTransform();
		Vector2f scale = transform->scale;
		transform->scale = scale * factor;
	}

	void Rotate(SpriteController* sprite, bool clockwise)
	{
		Rotate(sprite->getParent()->getTransform(), clockwise, sprite->getOmega());
	}

	void Rotate(CameraBehavior* camera, bool clockwise)
	{
		Rotate(camera->getParent()->getTransform(), clockwise, camera->getOmega());
	}

	void Translate(SpriteController* sprite, bool forward)
	{
		Translate(sprite->getParent()->getTransform(), forward, 0.5f);
	}

	void Translate(CameraBehavior* camera, bool forward)
	{
		Translate(camera->getParent()->getTransform(), forward, camera->getOmega());
	}

	void reset(std::map<Entity*, Transform> initialTransforms)
	{
		std::map<Entity*, Transform>::iterator it;

		for (it = initialTransforms.begin(); it != initialTransforms.end(); it++)
			it->first->setTransform(it->second);
	}
}

namespace app
{
	TransformButton::TransformButton(bool leftDirection) : m_positiveTransform(leftDirection)
	{
		Level* level = LevelManager::instance()->getCurrentLevel();
		m_yellowBlock = level->findEntity("yellowBlock")->getComponent<SpriteController>();
		m_blueBlock = level->findEntity("blueBlock")->getComponent<SpriteController>();
		m_inputModeSpriteRenderer = level->findEntity("inputModeButton")->getComponent<SpriteRenderer>();
		m_camera = Camera::instance()->getParent()->getComponent<CameraBehavior>();
		storeInitialTransforms();
	}

	void TransformButton::update()
	{
		if (InputManager::instance()->isTapDown(getParent()->getTransform()->getRect()))
			affect();
	}

	void TransformButton::affect()
	{
		std::string texAssetPath = m_inputModeSpriteRenderer->getTexturePath();

		if (texAssetPath == "Textures/RotateYellowSprite.png")
		{
			Rotate(m_yellowBlock, m_positiveTransform);
			return;
		}
		if (texAssetPath == "Textures/TranslateYellowSprite.png")
		{
			Translate(m_yellowBlock, m_positiveTransform);
			return;
		}
		if (texAssetPath == "Textures/TranslateBlueSprite.png")
		{
			Translate(m_blueBlock, m_positiveTransform);
			return;
		}
		if (texAssetPath == "Textures/RotateCamera.png")
		{
			Rotate(m_camera, m_positiveTransform);
			return;
		}
		if (texAssetPath == "Textures/TranslateCamera.png")
		{
			Translate(m_camera, m_positiveTransform);
			return;
		}

		if (texAssetPath == "Textures/ScaleCamera.png")
		{
			Scale(m_camera, m_positiveTransform);
			return;
		}

		if (texAssetPath == "Textures/Reset.png")
		{
			reset(m_initialTransforms);
			return;
		}

		throw Exception("The given texture asset path is not supported!");
	}

	void TransformButton::storeInitialTransforms()
	{
		storeInitialTransform(m_yellowBlock);
		storeInitialTransform(m_blueBlock);
		storeInitialTransform(m_camera);
	}

	void TransformButton::storeInitialTransform(Component * component)
	{
		Entity* parent = component->getParent();
		m_initialTransforms.insert(std::make_pair(parent, *parent->getTransform()));
	}
}

