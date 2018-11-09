#include "Transform.h"

namespace orb
{
	const Transform Transform::Identity = Transform();

	Transform operator*(const Transform& left, const Transform& right) 
	{
		return Transform(left.getPosition() + right.getPosition());
	}

}
