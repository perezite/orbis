#include "Camera.h"

#include "../Game/Transform.h"
#include "../Game/Entity.h"
#include "../Core/TimeManager.h"
using namespace Game;
using namespace Core;

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
		if (instance == NULL)
			throw Exception("No camera was attached in the level");

		return instance;
	}
}

namespace Components
{
	Camera::Camera()
	{
		if (instance != NULL)
			throw Exception("Only one camera at a time is allowed");

		instance = this;
	}

	Camera::~Camera()
	{
		instance = NULL;
	}

	Matrix3 Camera::GetInverseTransform()
	{
		Transform* transform = GetInstance()->GetParent()->GetTransform();
		Matrix3 invTransform;
		invTransform.Rotate2D(-transform->GetRotation());
		invTransform.Translate2D(-transform->GetPosition());
		return invTransform;
	}
}
