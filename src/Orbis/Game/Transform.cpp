#include "Transform.h"

namespace Game
{
	Matrix3 Transform::GetModelMatrix() const
	{
		Matrix3 mat;
		mat.Translate2D(position);
		mat.Rotate2D(rotation);
		mat.Scale2D(scale);
		return mat;
	}
}