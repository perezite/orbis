#pragma once

namespace base
{
	// represents a mathematical range
	template <class T>
	struct Range
	{
		// ctor
		Range()
			: min(0.0f), max(0.0f)
		{}

		// ctor
		Range(T min_, T max_)
			: min(min_), max(max_)
		{}

		// compute the difference of the range
		T diff() {
			return max - min;
		}

		// the minimum of the range
		T min;

		// the maximum of the range
		T max;
	};	
}