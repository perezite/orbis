#include "Transform.h"

namespace Game
{
	Matrix3 Transform::getModelMatrix() const
	{
		Matrix3 mat;
		mat.Translate2D(position);
		mat.Rotate2D(rotation);
		mat.Scale2D(scale);
		return mat;
	}

	Rect Transform::getRect() const
	{
		return Rect(position - scale * 0.5f, position + scale * 0.5f);
	}
}