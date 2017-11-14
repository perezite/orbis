#include "Transform.h"

namespace Game
{
	Matrix4 Transform::GetMatrix() const
	{
		Matrix4 mat;
		mat.Translate2D(m_position);
		mat.Rotate2D(m_rotation);
		return mat;
	}
}