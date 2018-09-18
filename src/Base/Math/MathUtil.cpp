#include "MathUtil.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>

namespace base
{
	float MathUtil::getPi()
	{
		return (float)M_PI;
	}

	float MathUtil::radianToDegrees(float radian)
	{
		return (radian / (2.0f * getPi())) * 360.0f;
	}

	float MathUtil::degreesToRadian(float degrees)
	{
		return (degrees / 360.0f) * 2.0f * getPi();
	}

	float MathUtil::getRandom()
	{
		return (float)rand() / (RAND_MAX);
	}

	float MathUtil::getRandom(float low, float high)
	{
		return MathUtil::getRandom() * (high - low) + low;
	}

	Vector2D MathUtil::getRandomOnUnitCircle()
	{
		float alpha = getRandom(0, 2.0f * getPi());
		return Vector2D(cosf(alpha), sinf(alpha));
	}

	bool MathUtil::approx(float val1, float val2, float eps)
	{
		return fabs(val1 - val2) < eps;
	}
}