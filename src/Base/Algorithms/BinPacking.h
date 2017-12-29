#pragma once

#include "../Math/Rect.h"
using namespace Math;

#include <vector>
#include <tuple>

namespace Algorithms
{
	// an algorithm to pack a list of rects into another rect (bin)
	class BinPacking
	{
	public:
		// execute the algorithm
		static std::vector<Rect> Execute(Rect bin, std::vector<Rect> origRects);

		// execute the algorithm up to n steps
		static std::vector<Rect> Execute(Rect bin, std::vector<Rect> origRects, unsigned int nSteps);

		// get partitions generated during last execution. Can be used for debugging
		static std::vector<Rect> GetPartitionBuffer() { return m_partitionBuffer; };

	protected:
		// sort rects by area
		static void SortRectsByArea(std::vector<Rect>& rects);

		// find the smallest partition where a rect still fits in
		static unsigned int FindSmallestFittingPartition(std::vector<Rect> m_partitionBuffer, Rect rect);

		// translate, such that the rect's bottom left coincides with the given point
		static void TranslateRect(Rect& rect, Vector2D bottomLeftTargetPos);

		// split the given partition with the given rect at the left bottom
		static std::tuple<Rect, Rect> Split(Rect partition, Rect rect);

	private:
		// partitions generated during last execution. Can be used for debugging
		static std::vector<Rect> m_partitionBuffer;
	};
}