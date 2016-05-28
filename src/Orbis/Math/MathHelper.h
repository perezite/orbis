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
	};
}