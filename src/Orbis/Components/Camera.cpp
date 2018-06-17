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

namespace Components
{
	Camera* Camera::m_instance = NULL;

	Camera* Camera::GetInstance()
	{
		Exception::Assert(m_instance != NULL, "No camera was attached in the level");

		return m_instance;
	}

	Camera::Camera() : Component()
	{
		Exception::Assert(m_instance == NULL, "Only one camera at a time is allowed");
		m_instance = this;
	}

	Camera::~Camera()
	{
		m_instance = NULL;
	}

	Vector2D Camera::ScreenSpaceToCameraSpace(Vector2D v)
	{
		return Vector2D(v.x, GetAspect() * v.y);
	}

	Matrix3 Camera::CalcViewMatrix(TransformSpace space)
	{
		if (space == TransformSpace::Camera)
			return Matrix3::GetEye();

		Transform* transform = GetInstance()->GetParent()->GetTransform();
		Matrix3 invTransform;
		invTransform.Rotate2D(-transform->rotation);
		invTransform.Translate2D(-transform->position);
		return invTransform;
	}

	// reference: http://www.songho.ca/opengl/gl_projectionmatrix.html (at the bottom)
	Matrix3 Camera::CalcProjectionMatrix(TransformSpace space)
	{
		Vector2D scale = 
			space == TransformSpace::World ? GetInstance()->GetParent()->GetTransform()->scale : Vector2D::One;
		Vector2D inverseScale = Vector2D(1.0f / scale.x, 1.0f / scale.y);
		Vector2D resolution = VideoManager::GetInstance()->GetWindow()->GetResolution();
		float inverseAspect = resolution.x / resolution.y;

		Matrix3 mat(2.0f * inverseScale.x, 0.0f, 0.0f, 
					0.0f, 2.0f * inverseAspect * inverseScale.y, 0.0f, 
					0.0f, 0.0f, 1.0f);
		return mat;
	}

	Matrix3 Camera::CalcCamMatrix(TransformSpace space)
	{
		return CalcProjectionMatrix(space) * CalcViewMatrix(space);
	}

	Vector2D Camera::GetSize()
	{
		Vector2D scale = GetInstance()->GetParent()->GetTransform()->scale;
		return Vector2D(scale.x, scale.y * GetAspect());
	}

	float Camera::GetAspect()
	{
		Vector2D resolution = VideoManager::GetInstance()->GetWindow()->GetResolution();
		return resolution.y / resolution.x;
	}
}
