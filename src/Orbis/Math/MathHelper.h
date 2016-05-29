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
		float DegreesToRadian(float degrees);
	};
}