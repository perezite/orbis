#pragma once

#include "Component.h"

#include "../../Orbis/Game/TransformSpace.h"
using namespace Game;

#include "../../Base/Math/Matrix3.h"
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

		// transform coordinates from screen space to camera space
		Vector2D ScreenSpaceToCameraSpace(Vector2D v);

		// get the view matrix (the inverse of the transform of the parent entity)
		Matrix3 CalcViewMatrix(TransformSpace space = TransformSpace::WorldSpace);

		// get the orthographic projection matrix
		Matrix3 CalcProjectionMatrix(TransformSpace space = TransformSpace::WorldSpace);

		// get the view-projection matrix
		Matrix3 CalcCamMatrix(TransformSpace space = TransformSpace::WorldSpace);

		// get the size of the camera in word coordinates
		Vector2D GetSize();

		// get the aspect ratio (height / width)
		float GetAspect();

	private:
		// singleton component instance
		static Camera* m_instance;
	};
}
