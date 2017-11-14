#include "Camera.h"

#include "../Game/Transform.h"
#include "../Game/Entity.h"
using namespace Game;

#include "../../Base/System/Exception.h"
using namespace System;

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

	Matrix4 Camera::GetInverseTransform()
	{
		Transform* transform = GetInstance()->GetParent()->GetTransform();
		Matrix4 invTransform;
		invTransform.Rotate2D(-transform->GetRotation());
		invTransform.Translate2D(-transform->GetPosition());
		return invTransform;
	}
}
