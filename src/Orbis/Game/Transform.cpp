#include "Transform.h"

namespace Game
{
	Matrix4 Transform::GetMatrix() const
	{
		Matrix4 mat;
		mat.Rotate2D(m_rotation);
		return mat;
	}
}