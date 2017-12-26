#include "Camera.h"

#include "../Game/Transform.h"
#include "../Game/Entity_v2.h"
#include "../Core/TimeManager.h"
#include "../Video/VideoManager.h"
using namespace Game;
using namespace Core;
using namespace Video;

#include "../../Base/System/Exception.h"
#include "../../Base/Math/MathHelper.h"
using namespace System;
using namespace Math;

namespace Components
{
	Components::Camera * Camera::GetInstance()
	{
		static Camera instance;
		return &instance;
	}

	Matrix3 Camera::GetViewMatrix()
	{
		// TODO: Use transform of the parent here
		Transform transform;
		Matrix3 invTransform;
		invTransform.Rotate2D(0.0f);
		invTransform.Translate2D(Vector2D::Zero);
		return invTransform;
	}

	// reference: http://www.songho.ca/opengl/gl_projectionmatrix.html (at the bottom)
	Matrix3 Camera::GetProjectionMatrix()
	{
		Vector2D scale = Vector2D::One;
		Vector2D inverseScale = Vector2D(1.0f / scale.GetX(), 1.0f / scale.GetY());
		Vector2D resolution = VideoManager::GetInstance()->GetResolution();
		float inverseAspect = resolution.GetX() / resolution.GetY();

		Matrix3 mat(2.0f * inverseScale.GetX(), 0.0f, 0.0f,
			0.0f, 2.0f * inverseAspect * inverseScale.GetY(), 0.0f,
			0.0f, 0.0f, 1.0f);

		return mat;
	}

	Vector2D Camera::GetSize()
	{
		Vector2D resolution = VideoManager::GetInstance()->GetResolution();
		Vector2D scale = Vector2D::One;
		float aspectRatio = resolution.GetY() / resolution.GetX();

		return Vector2D(scale.GetX(), scale.GetY() * aspectRatio);
	}
}