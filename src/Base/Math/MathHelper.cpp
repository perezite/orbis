#include "MathHelper.h"



#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>

namespace base
{
	namespace math
	{
		float MathHelper::getPi()
		{
			return (float)M_PI;
		}

		float MathHelper::radianToDegrees(float radian)
		{
			return (radian / (2.0f * getPi())) * 360.0f;
		}

		float MathHelper::degreesToRadian(float degrees)
		{
			return (degrees / 360.0f) * 2.0f * getPi();
		}

		float MathHelper::getRandom()
		{
			return (float)rand() / (RAND_MAX);
		}

		float MathHelper::getRandom(float low, float high)
		{
			return MathHelper::getRandom() * (high - low) + low;
		}

		Vector2D MathHelper::getRandomOnUnitCircle()
		{
			float alpha = getRandom(0, 2.0f * getPi());
			return Vector2D(cosf(alpha), sinf(alpha));
		}

		bool MathHelper::approx(float val1, float val2, float eps)
		{
			return fabs(val1 - val2) < eps;
		}
	}
}