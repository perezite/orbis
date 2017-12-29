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

		// update
		void Update();


	private:
		// the bin to be filled
		Rect m_bin;

		// the rects to fill into the bin
		std::vector<Rect> m_origRects;

		// the packed rects after bin packing
		std::vector<Rect> m_packedRects;

		// colors for the recgs
		std::vector<Color> m_rectColors;

		// current algorithmic bin pack step
		unsigned int m_currentStep;

		// number of rects
		static const unsigned int NUM_RECTS;

		// the range for generated extents
		static const Range EXTENTS_RANGE;
	};
}