#pragma once

#include "Component.h"

#include "../../Base/Math/Matrix4.h"
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

		// get the inverse camera transform (the inverse of the transform of the parent entity) 
		static Matrix4 GetInverseTransform();
	};
}