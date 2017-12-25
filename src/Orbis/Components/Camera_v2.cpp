#include "Camera_v2.h"

#include "../Game/Transform_v2.h"
#include "../Game/Entity_v2.h"
#include "../Core/TimeManager.h"
#include "../Video/VideoManager_v2.h"
using namespace Game;
using namespace Core;
using namespace Video;

#include "../../Base/System/Exception.h"
#include "../../Base/Math/MathHelper.h"
using namespace System;
using namespace Math;

namespace Components
{
	Components::Camera_v2 * Camera_v2::GetInstance()
	{
		static Camera_v2 instance;
		return &instance;
	}

	Matrix3 Camera_v2::GetViewMatrix()
	{
		Transform_v2 transform;
		Matrix3 invTransform;
		invTransform.Rotate2D(0.0f);
		invTransform.Translate2D(Vector2D::Zero);
		return invTransform;
	}

	// reference: http://www.songho.ca/opengl/gl_projectionmatrix.html (at the bottom)
	Matrix3 Camera_v2::GetProjectionMatrix()
	{
		Vector2D scale = Vector2D::One;
		Vector2D inverseScale = Vector2D(1.0f / scale.GetX(), 1.0f / scale.GetY());
		Vector2D resolution = VideoManager_v2::GetInstance()->GetResolution();
		float inverseAspect = resolution.GetX() / resolution.GetY();

		Matrix3 mat(2.0f * inverseScale.GetX(), 0.0f, 0.0f,
			0.0f, 2.0f * inverseAspect * inverseScale.GetY(), 0.0f,
			0.0f, 0.0f, 1.0f);

		return mat;
	}

	Vector2D Camera_v2::GetSize()
	{
		Vector2D resolution = VideoManager_v2::GetInstance()->GetResolution();
		Vector2D scale = Vector2D::One;
		float aspectRatio = resolution.GetY() / resolution.GetX();

		return Vector2D(scale.GetX(), scale.GetY() * aspectRatio);
	}
}