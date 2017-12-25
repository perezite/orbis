#pragma once

#include "Component.h"

#include "../../Base/Math/Matrix3.h"
#include "../../Base/Math/Vector2D.h"
using namespace Math;

namespace Components
{
	// The camera
	class Camera_v2 : public Component
	{
	public:
		// get singleton
		static Components::Camera_v2* GetInstance();

		// get the view matrix (the inverse of the transform of the parent entity) 
		Matrix3 GetViewMatrix();

		// get the orthographic projection matrix
		Matrix3 GetProjectionMatrix();

		// get the size of the camera in word coordinates
		Vector2D GetSize();
	};
}