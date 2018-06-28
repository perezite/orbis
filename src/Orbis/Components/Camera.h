#pragma once

#include "Component.h"

#include "../../Orbis/Game/TransformSpace.h"
using namespace orbis::game;

#include "../../Base/Math/Matrix3.h"
#include "../../Base/Math/Vector2D.h"
using namespace base::math;

namespace orbis
{
	namespace components
	{
		// The camera
		class Camera : public Component
		{
		public:
			// get singleton component
			static Camera* getInstance();

			// ctor
			Camera();

			// dtor
			virtual ~Camera();

			// transform coordinates from screen space to camera space
			Vector2D screenSpaceToCameraSpace(Vector2D v);

			// get the view matrix (the inverse of the transform of the parent entity)
			Matrix3 calcViewMatrix(TransformSpace space = TransformSpace::World);

			// get the orthographic projection matrix
			Matrix3 calcProjectionMatrix(TransformSpace space = TransformSpace::World);

			// get the view-projection matrix
			Matrix3 calcCamMatrix(TransformSpace space = TransformSpace::World);

			// get the size of the camera in world coordinates
			Vector2D getSize();

			// get the aspect ratio (height / width)
			float getAspect();

		private:
			// singleton component instance
			static Camera* m_instance;
		};
	}
}