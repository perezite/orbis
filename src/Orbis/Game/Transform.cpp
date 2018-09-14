#include "../Orbis.h"

namespace orb
{
	namespace game
	{
		Matrix3 Transform::getModelMatrix() const
		{
			Matrix3 mat;
			mat.translate2D(position);
			mat.rotate2D(rotation);
			mat.scale2D(scale);
			return mat;
		}

		Rect Transform::getRect() const
		{
			return Rect(position - scale * 0.5f, position + scale * 0.5f);
		}
	}
}