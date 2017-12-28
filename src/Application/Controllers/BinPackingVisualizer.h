#pragma once

#include "../../Orbis/Components/Component.h"
using namespace Components;

#include "../../Base/Math/Rect.h"
using namespace Math;

#include <vector>

namespace Controllers
{
	class BinPackingVisualizer : public Component
	{
	public:
		BinPackingVisualizer();

		// render
		void Render();

	private:
		// the rects to fill into the bin
		std::vector<Rect> m_rects;

		// the bin to be filled
		Rect m_bin;
	};
}