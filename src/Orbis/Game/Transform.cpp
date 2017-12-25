#include "Transform.h"

namespace Game
{
	Matrix3 Transform::GetModelMatrix() const
	{
		Matrix3 mat;
		mat.Translate2D(m_position);
		mat.Rotate2D(m_rotation);
		mat.Scale2D(m_scale);
		return mat;
	}
}