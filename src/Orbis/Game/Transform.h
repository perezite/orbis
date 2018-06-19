#pragma once

#include "TransformSpace.h"

#include "../../Base/Math/Vector2D.h"
#include "../../Base/Math/Matrix3.h"
#include "../../Base/Math/Rect.h"
using namespace Math;

namespace Game
{
	struct Transform
	{
	public:
		// ctor
		Transform()
			: position(Vector2D::Zero), rotation(0.0f), scale(Vector2D::One), transformSpace(TransformSpace::World)
		{}

		// ctor
		Transform(Vector2D position_, float rotation_, Vector2D scale_, TransformSpace transformSpace_ = TransformSpace::World)
			: position(position_), rotation(rotation_), scale(scale_), transformSpace(transformSpace_)
		{}

		// get the model matrix
		Matrix3 getModelMatrix() const;

		// get the transform's unrotated rect
		Rect getRect() const;
	
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