#pragma once

#include "Component.h"

#include "../../Base/Math/Matrix4.h"
#include "../../Base/Math/Vector2D.h"
using namespace Math;

namespace Components
{
	// The camera
	class Camera : public Component
	{
	public:
		// ctor
		Camera();

		// dtor
		virtual ~Camera();

		// get the view matrix (the inverse of the transform of the parent entity) 
		static Matrix3 GetViewMatrix();

		// get the orthographic projection matrix
		static Matrix4 GetProjectionMatrix();

		// get the size of the camera in word coordinates
		static Vector2D GetSize();
	};
}