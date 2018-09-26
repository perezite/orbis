#pragma once

#include "../../Orbis/Orbis.h"
using namespace orb;

#include "../../Base/Base.h"
using namespace base;

#include <vector>
#include <tuple>

namespace app
{
	// visualizes a bin packing algorithm
	class BinPackingVisualizer : public Component
	{
	public:
		BinPackingVisualizer();

		// render
		void renderDebug();

		// updateLevel
		void update();


	private:
		// the rects to fill into the bin
		std::vector<Rect> m_origRects;

		// the packed rects after bin packing
		std::vector<std::vector<Rect>> m_packedRects;

		// colors for the recgs
		std::vector<Color> m_rectColors;

		// current algorithmic bin pack step
		unsigned int m_currentStep;

		// number of rects
		static const unsigned int NUM_RECTS;

		// the range for generated extents
		static const Range<float> EXTENTS_RANGE;

		// the size of the bin
		static const Rect BIN;
	};
}