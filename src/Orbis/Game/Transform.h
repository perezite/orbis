#pragma once

#include "TransformSpace.h"

#include "../../Base/Math/Vector2D.h"
#include "../../Base/Math/Matrix3.h"
using namespace Math;

namespace Game
{
	struct Transform
	{
	public:
		// ctor
		Transform()
			: position(Vector2D::Zero), rotation(0.0f), scale(Vector2D::One), transformSpace(TransformSpace::WorldSpace)
		{}

		// ctor
		Transform(Vector2D position_, float rotation_, Vector2D scale_, TransformSpace transformSpace_ = TransformSpace::WorldSpace)
			: position(position_), rotation(rotation_), scale(scale_), transformSpace(transformSpace_)
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

		// the transform space
		TransformSpace transformSpace;

	};
}