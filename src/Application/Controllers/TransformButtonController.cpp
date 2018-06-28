#include "TransformButtonController.h"

#include "../../Orbis/Input/InputManager.h"
#include "../../Orbis/Core/TimeManager.h"
#include "../../Orbis/Game/Transform.h"
#include "../../Base/Math/Vector2D.h"
#include "../../Base/Math/Rect.h"
using namespace orb::input;
using namespace orb::core;
using namespace orb::game;
using namespace base::math;

namespace 
{
	using namespace controllers;

	void Rotate(Transform* transform, bool clockwise, float omega)
	{
		omega = clockwise ? -omega : omega;
		float alpha = transform->rotation;
		transform->rotation = alpha + TimeManager::getInstance()->getDeltaSeconds() * omega;
	}

	void Translate(Transform* transform, bool forward, float speed)
	{
		speed = forward ? speed : -speed;
		Vector2D position = transform->position;
		Vector2D translation = Matrix3::rotation2D(transform->rotation) * Vector2D(TimeManager::getInstance()->getDeltaSeconds() * speed, 0.0f);
		transform->position = position + translation;
	}

	void Scale(CameraController *camera, bool positive)
	{
		float dt = TimeManager::getInstance()->getDeltaSeconds();
		float factor = positive ? 1 - dt * 0.5f : 1 + dt * 0.5f;
		Transform* transform = camera->getParent()->getTransform();
		Vector2D scale = transform->scale;
		transform->scale = scale * factor;
	}

	void Rotate(SpriteController* sprite, bool clockwise)
	{
		Rotate(sprite->getParent()->getTransform(), clockwise, sprite->getOmega());
	}

	void Rotate(CameraController* camera, bool clockwise)
	{
		Rotate(camera->getParent()->getTransform(), clockwise, camera->getOmega());
	}

	void Translate(SpriteController* sprite, bool forward)
	{
		Translate(sprite->getParent()->getTransform(), forward, 0.5f);
	}

	void Translate(CameraController* camera, bool forward)
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

namespace controllers
{
	void TransformButtonController::update()
	{
		InputManager* input = InputManager::getInstance();

		if (input->isTapDown(getParent()->getTransform()->getRect()))
			affect();
	}

	void TransformButtonController::affect()
	{
		std::string texAssetPath = m_inputModeSpriteRenderer->getTexture()->getAssetPath();

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

	void TransformButtonController::storeInitialTransforms()
	{
		storeInitialTransform(m_yellowBlock);
		storeInitialTransform(m_blueBlock);
		storeInitialTransform(m_camera);
	}

	void TransformButtonController::storeInitialTransform(Component * component)
	{
		Entity* parent = component->getParent();
		m_initialTransforms.insert(std::make_pair(parent, *parent->getTransform()));
	}
}

