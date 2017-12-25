#pragma once

#include "../../Base/Math/Vector2D.h"
#include "../../Base/Math/Matrix3.h"
using namespace Math;

namespace Game
{
	struct Transform_v2
	{
	public:
		// ctor
		Transform_v2()
			: position(Vector2D::Zero), rotation(0.0f), scale(Vector2D::One)
		{}

		// get the model matrix
		Matrix3 GetModelMatrix() const;

	public:
		// the position
		Vector2D position;

		// the rotation
		float rotation;

		// the scale
		Vector2D scale;
	};
}