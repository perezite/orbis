#pragma once

namespace Math
{
	// represents a mathematical range
	struct Range
	{
		// ctor
		Range() 
			: min(0.0f), max(0.0f) 
		{}

		// ctor
		Range(float min_, float max_) 
			: min(min_), max(max_) 
		{}

		// the minimum of the range
		float min;

		// the maximum of the range
		float max;
	};
}