#include "MathHelper.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>

namespace Math
{
	float MathHelper::GetPi()
	{
		return (float)M_PI;
	}

	float MathHelper::RadianToDegrees(float radian)
	{
		return (radian / (2.0f * GetPi())) * 360.0f;
	}

	float MathHelper::DegreesToRadian(float degrees)
	{
		return (degrees / 360.0f) * 2.0f * GetPi();
	}

	float MathHelper::GetRandom()
	{
		return (float)rand() / (RAND_MAX);
	}
}
