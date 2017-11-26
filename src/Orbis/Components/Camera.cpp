#include "Camera.h"

#include "../Game/Transform.h"
#include "../Game/Entity.h"
#include "../Core/TimeManager.h"
#include "../Video/VideoManager.h"
using namespace Game;
using namespace Core;
using namespace Video;

#include "../../Base/System/Exception.h"
#include "../../Base/Math/MathHelper.h"
using namespace System;
using namespace Math;

namespace
{
	// singleton camera instance
	static Components::Camera* instance = NULL;

	Components::Camera* GetInstance()
	{
		Exception::Assert(instance != NULL, "No camera was attached in the level");

		return instance;
	}
}

namespace Components
{
	Camera::Camera()
	{
		Exception::Assert(instance == NULL, "Only one camera at a time is allowed");
		instance = this;
	}

	Camera::~Camera()
	{
		instance = NULL;
	}

	Matrix3 Camera::GetViewMatrix()
	{
		Transform* transform = GetInstance()->GetParent()->GetTransform();
		Matrix3 invTransform;
		invTransform.Rotate2D(-transform->GetRotation());
		invTransform.Translate2D(-transform->GetPosition());
		return invTransform;
	}

	// reference: http://www.songho.ca/opengl/gl_projectionmatrix.html (at the bottom)
	Matrix4 Camera::GetProjectionMatrix()
	{
		Vector2D scale = GetInstance()->GetParent()->GetTransform()->GetScale();
		Vector2D inverseScale = Vector2D(1.0f / scale.GetX(), 1.0f / scale.GetY());
		Vector2D resolution = VideoManager::GetInstance()->GetResolution();
		float inverseAspect = resolution.GetX() / resolution.GetY();

		Matrix4 mat(2.0f * inverseScale.GetX(), 0.0f, 0.0f, 0.0f,
			0.0f, 2.0f * inverseAspect * inverseScale.GetY(), 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);

		return mat;
	}

	Vector2D Camera::GetSize()
	{
		Vector2D resolution = VideoManager::GetInstance()->GetResolution();
		Vector2D scale = GetInstance()->GetParent()->GetTransform()->GetScale();
		float aspectRatio = resolution.GetY() / resolution.GetX();
		
		return Vector2D(scale.GetX(), scale.GetY() * aspectRatio);
	}
}
