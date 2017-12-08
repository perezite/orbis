#include "InputController.h"

#include "SpriteController.h"
using namespace Controllers;

#include "../../Orbis/Input/InputManager.h"
#include "../../Orbis/Core/TimeManager.h"
#include "../../Orbis/Core/LogHelper.h"
#include "../../Orbis/Game/Transform.h"
#include "../../Orbis/Game/Entity.h"
#include "../../Orbis/Components/Camera.h"
#include "../../Base/Math/Matrix3.h"
#include "../../Base/System/StringHelper.h"
using namespace Input;
using namespace Core;
using namespace Game;
using namespace Components;
using namespace Math;

#include <algorithm>

namespace
{
	void Rotate(Transform* transform, bool clockwise, float omega)
	{
		omega = clockwise ? -omega : omega;
		float alpha = transform->GetRotation();
		transform->SetRotation(alpha + TimeManager::GetInstance()->GetDeltaSeconds() * omega);
	}	

	void Translate(Transform* transform, bool forward, float speed)
	{
		speed = forward ? speed : -speed;
		Vector2D position = transform->GetPosition();
		Vector2D translation = Matrix3::Rotation2D(transform->GetRotation()) * Vector2D(TimeManager::GetInstance()->GetDeltaSeconds() * speed, 0.0f);
		transform->SetPosition(position + translation);
	}

	void Scale(CameraController *camera, bool positive)
	{
		float dt = TimeManager::GetInstance()->GetDeltaSeconds();
		float factor = positive ? 1 - dt * 0.5f : 1 + dt * 0.5f;
		Transform* transform = camera->GetParent()->GetTransform();
		Vector2D scale = transform->GetScale();
		transform->SetScale(scale * factor);
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
	void InputController::Update()
	{
		static InputManager* inputManager = InputManager::GetInstance();

		if (inputManager->IsTapGoingDown())
		{
			Vector2D tapPosition = inputManager->GetTapPosition();

			// left top tap
			if (tapPosition.GetX() < 0 && tapPosition.GetY() >= 0.0f)
				Cycle();

			// right top tap
			if (tapPosition.GetX() >= 0 && tapPosition.GetY() >= 0)
			{
				InputManager::GetInstance()->SetQuitEvent();
			}
		}

		if (inputManager->IsTapDown())
		{
			Vector2D tapPosition = inputManager->GetTapPosition();

			// left bottom tap
			if (tapPosition.GetX() < 0 && tapPosition.GetY() < 0.0f)
			{
				Affect(false);
			}

			// right bottom tap
			if (tapPosition.GetX() >= 0 && tapPosition.GetY() < 0.0f)
			{
				Affect(true);
			}
		}
	}

	void InputController::Cycle()
	{
		// get new texture
		std::vector<Texture*>::iterator previousTextureIt = std::find(m_inputModeOverlayTextures.begin(), m_inputModeOverlayTextures.end(), m_inputModeOverlaySpriteRenderer->GetTexture());
		std::vector<Texture*>::iterator currentTextureIt = ++previousTextureIt;

		// update sprite renderer
		Texture* nextTexture = currentTextureIt != m_inputModeOverlayTextures.end() ? (*currentTextureIt) : m_inputModeOverlayTextures.front();
		m_inputModeOverlaySpriteRenderer->SetTexture(nextTexture);
	}

	void InputController::InitializeComponent(Component * component)
	{
		Entity* parent = component->GetParent();
		m_initialTransforms.insert(std::make_pair(parent, *parent->GetTransform()));
	}

	void InputController::Affect(bool positive)
	{
		std::string texAssetPath = m_inputModeOverlaySpriteRenderer->GetTexture()->GetAssetPath();
		
		if (texAssetPath == "Textures/RotateYellowSprite.png")
		{
			Rotate(m_yellowBrick, positive);
			return;
		}
		if (texAssetPath == "Textures/TranslateYellowSprite.png")
		{
			Translate(m_yellowBrick, positive);
			return;
		}
		if (texAssetPath == "Textures/TranslateBlueSprite.png")
		{
			Translate(m_blueBrick, positive);
			return;
		}
		if (texAssetPath == "Textures/RotateCamera.png")
		{
			Rotate(m_camera, positive);
			return;
		}
		if (texAssetPath == "Textures/TranslateCamera.png")
		{
			Translate(m_camera, positive);
			return;
		}

		if (texAssetPath == "Textures/ScaleCamera.png")
		{
			Scale(m_camera, positive);
			return;
		}

		if (texAssetPath == "Textures/Reset.png")
		{
			Reset(m_initialTransforms);
			return;
		}

		throw Exception("The given texture asset path is not supported!");
	}
}