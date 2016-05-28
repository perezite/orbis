#include "MathHelper.h"

#define _USE_MATH_DEFINES
#include <math.h>


namespace Math
{
	float MathHelper::GetPi()
	{
		return M_PI;
	}

	float MathHelper::RadianToDegrees(float radian)
	{
		return (radian / (2.0f * GetPi())) * 360.0f;
	}
}
