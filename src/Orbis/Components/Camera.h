#pragma once

#include "Component.h"

#include "../../Orbis/Game/TransformSpace.h"
using namespace Game;

#include "../../Base/Math/Matrix4.h"
#include "../../Base/Math/Vector2D.h"
using namespace Math;

namespace Components
{
	// The camera
	class Camera : public Component
	{
	public:
		// get singleton component
		static Camera* GetInstance();

		// ctor
		Camera();

		// dtor
		virtual ~Camera();

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
		Matrix3 CalcViewMatrix(TransformSpace space = TransformSpace::WorldSpace);

		// get the orthographic projection matrix
		Matrix3 CalcProjectionMatrix(TransformSpace space = TransformSpace::WorldSpace);

		// get the view-projection matrix
		Matrix3 CalcCamMatrix(TransformSpace space = TransformSpace::WorldSpace);

		// get the size of the camera in word coordinates
		Vector2D GetSize();

	private:
		// singleton component instance
		static Camera* m_instance;
	};
}
