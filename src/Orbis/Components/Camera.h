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
		Vector2f screenSpaceToCameraSpace(Vector2f v);

		// get the view matrix (the inverse of the transform of the parent entity)
		Matrix3 calcViewMatrix(TransformSpace space = TransformSpace::World);

		// get the orthographic projection matrix
		Matrix3 calcProjectionMatrix(TransformSpace space = TransformSpace::World);

		// get the camera matrix
		const Matrix3& getCamMatrix(TransformSpace space = TransformSpace::World) const;

		// get the size of the camera in world coordinates
		Vector2f getSize();

		// get the aspect ratio (height / width)
		float getAspect();

	protected:
		// get the view-projection matrix
		Matrix3 calcCamMatrix(TransformSpace space = TransformSpace::World);

	private:
		// singleton component instance
		static Camera* m_instance;

		// the local cam matrix
		Matrix3 m_localCamMatrix;

		// the world cam matrix
		Matrix3 m_worldCamMatrix;

	};
}