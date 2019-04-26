#pragma once

#include "TransformSpace.h"

#include "../../Base/Base.h"
using namespace base;

namespace orb
{
	struct Transform
	{
	public:
		// ctor
		Transform()
			: position(Vector2f::Zero), rotation(0.0f), scale(Vector2f::One), transformSpace(TransformSpace::World)
		{ }

		// ctor
		Transform(Vector2f position_, float rotation_, Vector2f scale_, TransformSpace transformSpace_ = TransformSpace::World)
			: position(position_), rotation(rotation_), scale(scale_), transformSpace(transformSpace_)
		{ }

		// get the model matrix
		Matrix3 getModelMatrix() const;

		// get the transform's unrotated rect
		Rect getRect() const;

	public:
		// the position
		Vector2f position;

		// the rotation
		float rotation;

		// the scale
		Vector2f scale;

		// the transform space
		TransformSpace transformSpace;
	};
}