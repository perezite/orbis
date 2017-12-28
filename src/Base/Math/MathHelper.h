#pragma once

namespace Math
{
	// Helpers for math
	class MathHelper
	{
	public:
		// get the number Pi
		static float GetPi();

		// convert angle in radian to angle in degrees
		static float RadianToDegrees(float radian);

		// convert angle in degrees to angle in radian
		static float DegreesToRadian(float degrees);

		// a random value between (0, 1)
		static float GetRandom();

		// a random value within the given range
		static float GetRandom(float low, float hight);

		// check whether two values are closer than eps
		static float Approx(float val1, float val2, float eps);
	};
}