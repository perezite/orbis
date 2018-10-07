#pragma once

#include "Component.h"

#include "../../Orbis/Game/TransformSpace.h"

#include "../../Base/Base.h"
using namespace base;

namespace orb
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

		// override
		void update();

		// transform coordinates from screen space to camera space
		Vector2D screenSpaceToCameraSpace(Vector2D v);

		// get the view matrix (the inverse of the transform of the parent entity)
		Matrix3 calcViewMatrix(TransformSpace space = TransformSpace::World);

		// get the orthographic projection matrix
		Matrix3 calcProjectionMatrix(TransformSpace space = TransformSpace::World);

		// get the view-projection matrix
		Matrix3 calcCamMatrix(TransformSpace space = TransformSpace::World);

		Matrix3& getCamMatrix(TransformSpace space);

		// get the size of the camera in world coordinates
		Vector2D getSize();

		// get the aspect ratio (height / width)
		float getAspect();

	private:
		// singleton component instance
		static Camera* m_instance;

		// local cam matrix
		Matrix3 m_localCamMatrix;

		// world cam matrix
		Matrix3 m_worldCamMatrix;
	};
}