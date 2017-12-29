#pragma once

#include "../../Orbis/Components/Component.h"
#include "../../Orbis/Video/Color.h"
using namespace Components;
using namespace Video;

#include "../../Base/Math/Rect.h"
#include "../../Base/Math/Range.h"
using namespace Math;

#include <vector>
#include <tuple>

namespace Controllers
{
	// visualizes a bin packing algorithm
	class BinPackingVisualizer : public Component
	{
	public:
		BinPackingVisualizer();

		// render
		void Render();

	protected:
		// perform packing
		// reference: https://www.youtube.com/watch?v=rVp5--Gx6Ks
		void Pack();

		// sort rects by area
		void SortRectsByArea();

		// find the smallest partition where a rect still fits in
		unsigned int FindSmallestFittingPartition(std::vector<Rect> m_partitions, Rect rect);

		// translate, such that the rect's bottom left coincides with the given point
		void TranslateRect(Rect& rect, Vector2D bottomLeftTargetPos);

		// split the given partition with the given rect at the left bottom
		std::tuple<Rect, Rect> Split(Rect partition, Rect rect);

	private:
		// the rects to fill into the bin
		std::vector<Rect> m_rects;

		// colors for the recgs
		std::vector<Color> m_rectColors;

		// the bin to be filled
		Rect m_bin;

		// number of rects
		static const unsigned int NUM_RECTS;

		// the range for generated extents
		static const Range EXTENTS_RANGE;
	};
}