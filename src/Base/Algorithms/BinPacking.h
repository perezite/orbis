#pragma once

#include "../Math/Rect.h"
using namespace base;

#include <vector>
#include <tuple>

namespace base
{
	// an algorithm to tightly pack a list of rects into an unlimited supply of bins of equal size
	// reference: https://www.youtube.com/watch?v=rVp5--Gx6Ks
	class BinPacking
	{
	public:
		// execute the algorithm
		static std::vector<std::vector<Rect>> calculate(Rect bin, std::vector<Rect> rects);

		// execute the algorithm up to n steps
		static std::vector<std::vector<Rect>> calculate(Rect bin, std::vector<Rect> rects, unsigned int numSteps);

		// get partitions generated during last execution of last bin. Can be used for debugging
		static std::vector<Rect> getPartitionBuffer() { return m_partitionBuffer; };

	protected:
		// pack the rects into the bin. Inserted rects are removed from the passed list
		static std::vector<Rect> pack(Rect bin, std::vector<Rect>& rects, unsigned int numSteps);

		// sort rects by area
		static void sortRectsByArea(std::vector<Rect>& rects);

		// find the smallest partition where a rect still fits in or return -1 if no fitting partition was found
		static int findSmallestFittingPartition(std::vector<Rect> m_partitionBuffer, Rect rect);

		// translate, such that the rect's bottom left coincides with the given point
		static void translateRect(Rect& rect, Vector2D bottomLeftTargetPos);

		// split the given partition with the given rect at the left bottom
		static std::tuple<Rect, Rect> split(Rect partition, Rect rect);

	private:
		// partitions generated during last execution of last bin. Can be used for debugging
		static std::vector<Rect> m_partitionBuffer;
	};
	
}