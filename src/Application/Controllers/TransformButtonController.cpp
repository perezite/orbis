#include "TransformButtonController.h"

#include "../../Orbis/Input/InputManager.h"
#include "../../Orbis/Core/TimeManager.h"
#include "../../Orbis/Game/Transform.h"
#include "../../Base/Math/Vector2D.h"
#include "../../Base/Math/Rect.h"
using namespace Input;
using namespace Core;
using namespace Game;
using namespace Math;

namespace 
{
	using namespace Controllers;

	void Rotate(Transform* transform, bool clockwise, float omega)
	{
		omega = clockwise ? -omega : omega;
		float alpha = transform->rotation;
		transform->rotation = alpha + TimeManager::getInstance()->GetDeltaSeconds() * omega;
	}

	void Translate(Transform* transform, bool forward, float speed)
	{
		speed = forward ? speed : -speed;
		Vector2D position = transform->position;
		Vector2D translation = Matrix3::Rotation2D(transform->rotation) * Vector2D(TimeManager::getInstance()->GetDeltaSeconds() * speed, 0.0f);
		transform->position = position + translation;
	}

	void Scale(CameraController *camera, bool positive)
	{
		float dt = TimeManager::getInstance()->GetDeltaSeconds();
		float factor = positive ? 1 - dt * 0.5f : 1 + dt * 0.5f;
		Transform* transform = camera->GetParent()->GetTransform();
		Vector2D scale = transform->scale;
		transform->scale = scale * factor;
	}

	void Rotate(SpriteController* sprite, bool clockwise)
	{
		Rotate(sprite->GetParent()->GetTransform(), clockwise, sprite->GetOmega());
	}

	void Rotate(CameraController* camera, bool clockwise)
	{
		Rotate(camera->GetParent()->GetTransform(), clockwise, camera->GetOmega());
	}

	void Translate(SpriteController* sprite, bool forward)
	{
		Translate(sprite->GetParent()->GetTransform(), forward, 0.5f);
	}

	void Translate(CameraController* camera, bool forward)
	{
		Translate(camera->GetParent()->GetTransform(), forward, camera->GetOmega());
	}

	void Reset(std::map<Entity*, Transform> initialTransforms)
	{
		std::map<Entity*, Transform>::iterator it;

		for (it = initialTransforms.begin(); it != initialTransforms.end(); it++)
			it->first->SetTransform(it->second);
	}
}

namespace Controllers
{
	void TransformButtonController::Update()
	{
		InputManager* input = InputManager::getInstance();

		if (input->IsTapDown(GetParent()->GetTransform()->GetRect()))
			Affect();
	}

	void TransformButtonController::Affect()
	{
		std::string texAssetPath = m_inputModeSpriteRenderer->getTexture()->GetAssetPath();

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
			Reset(m_initialTransforms);
			return;
		}

		throw Exception("The given texture asset path is not supported!");
	}

	void TransformButtonController::StoreInitialTransforms()
	{
		StoreInitialTransform(m_yellowBlock);
		StoreInitialTransform(m_blueBlock);
		StoreInitialTransform(m_camera);
	}

	void TransformButtonController::StoreInitialTransform(Component * component)
	{
		Entity* parent = component->GetParent();
		m_initialTransforms.insert(std::make_pair(parent, *parent->GetTransform()));
	}
}

