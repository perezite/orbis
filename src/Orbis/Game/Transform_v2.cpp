#include "Transform_v2.h"

Matrix3 Game::Transform_v2::GetModelMatrix() const
{
	Matrix3 mat;
	mat.Translate2D(position);
	mat.Rotate2D(rotation);
	mat.Scale2D(scale);
	return mat;
}
