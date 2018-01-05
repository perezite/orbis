#pragma once

#include "../Math/Rect.h"
using namespace Math;

#include <vector>
#include <tuple>

namespace Algorithms
{
	// an algorithm to tightly pack a list of rects into an unlimited supply of bins of equal size
	// reference: https://www.youtube.com/watch?v=rVp5--Gx6Ks
	class BinPacking
	{
	public:
		// execute the algorithm
		static std::vector<std::vector<Rect>> Execute(Rect bin, std::vector<Rect> rects);

		// execute the algorithm up to n steps
		static std::vector<std::vector<Rect>> Execute(Rect bin, std::vector<Rect> rects, unsigned int numSteps);

		// get partitions generated during last execution of last bin. Can be used for debugging
		static std::vector<Rect> GetPartitionBuffer() { return m_partitionBuffer; };

	protected:
		// pack the rects into the bin. Inserted rects are removed from the passed list
		static std::vector<Rect> Pack(Rect bin, std::vector<Rect>& rects, unsigned int numSteps);

		// sort rects by area
		static void SortRectsByArea(std::vector<Rect>& rects);

		// find the smallest partition where a rect still fits in or return -1 if no fitting partition was found
		static int FindSmallestFittingPartition(std::vector<Rect> m_partitionBuffer, Rect rect);

		// translate, such that the rect's bottom left coincides with the given point
		static void TranslateRect(Rect& rect, Vector2D bottomLeftTargetPos);

		// split the given partition with the given rect at the left bottom
		static std::tuple<Rect, Rect> Split(Rect partition, Rect rect);

	private:
		// partitions generated during last execution of last bin. Can be used for debugging
		static std::vector<Rect> m_partitionBuffer;
	};
}