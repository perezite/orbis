#include "Math.h"



#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>

namespace base
{
	namespace math
	{
		float Math::getPi()
		{
			return (float)M_PI;
		}

		float Math::radianToDegrees(float radian)
		{
			return (radian / (2.0f * getPi())) * 360.0f;
		}

		float Math::degreesToRadian(float degrees)
		{
			return (degrees / 360.0f) * 2.0f * getPi();
		}

		float Math::getRandom()
		{
			return (float)rand() / (RAND_MAX);
		}

		float Math::getRandom(float low, float high)
		{
			return Math::getRandom() * (high - low) + low;
		}

		Vector2D Math::getRandomOnUnitCircle()
		{
			float alpha = getRandom(0, 2.0f * getPi());
			return Vector2D(cosf(alpha), sinf(alpha));
		}

		bool Math::approx(float val1, float val2, float eps)
		{
			return fabs(val1 - val2) < eps;
		}
	}
}