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

		// get singleton
		static Camera* GetInstance();

		// get the view matrix (the inverse of the transform of the parent entity) 
		// TODO: Remove after refactoring
		static Matrix3 GetViewMatrix_old() { return Matrix3(); }

		// get the orthographic projection matrix
		// TODO: Remove after refactoring
		static Matrix4 GetProjectionMatrix_old(bool applyScaling) { return Matrix4(); }

		// get the size of the camera in word coordinates
		// TODO: Remove after refactoring
		static Vector2D GetSize_old() { return Vector2D(); }

		// get the view matrix (the inverse of the transform of the parent entity)
		Matrix3 GetViewMatrix();

		// get the orthographic projection matrix
		Matrix3 GetProjectionMatrix();

		// get the size of the camera in word coordinates
		Vector2D GetSize();
	};
}
