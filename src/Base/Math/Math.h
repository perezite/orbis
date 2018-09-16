#pragma once

#include "Vector2D.h"

namespace base
{
	namespace math
	{
		// Helpers for math
		class Math
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
			static Vector2D getRandomOnUnitCircle();

			// check whether two values are closer than eps
			static bool approx(float val1, float val2, float eps);
		};
	}
}