#pragma once

#include "Vector2.h"

namespace base
{
	// Helpers for math
	class MathUtil
	{
	public:
		// get the number Pi
		static float getPi();

		// convert angle in radian to angle in degrees
		static float radianToDegrees(float radian);

		// convert angle in degrees to angle in radian
		static float degreesToRadian(float degrees);

		// a random value between (0, 1)
		static float getRandom();

		// a random value within the given range
		static float getRandom(float low, float hight);

		// a random vector on the unit circle
		static Vector2f getRandomOnUnitCircle();

		// check whether two values are closer than eps
		static bool approx(float val1, float val2, float eps);

		// compute the median
		static float median(std::vector<float> samples);

		// compute the next power of two
		static int nextPowerOfTwo(int number);
	};
}