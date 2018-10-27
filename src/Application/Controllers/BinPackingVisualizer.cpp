#include "BinPackingVisualizer.h"

#include "../../Base/Base.h"
using namespace base;

#include "../../Orbis/Orbis.h"
using namespace orb;

#include <iostream>
#include <limits>
#include <algorithm>

namespace app
{
	const unsigned int BinPackingVisualizer::NUM_RECTS = 15;

	const Rect BinPackingVisualizer::BIN(-0.2f, -0.2f, 0.2f, 0.2f);

	const Range<float> BinPackingVisualizer::EXTENTS_RANGE(0.1f, 0.2f);

	BinPackingVisualizer::BinPackingVisualizer()
		: m_currentStep(0)
	{
		// insert rects and colors
		for (unsigned int i = 0; i < NUM_RECTS; i++)
		{
			float width = MathUtil::getRandom(EXTENTS_RANGE.min, EXTENTS_RANGE.max);
			float height = MathUtil::getRandom(EXTENTS_RANGE.min, EXTENTS_RANGE.max);
			Vector2f leftBottom(-width / 2.0f, -height / 2.0f);
			Vector2f rightTop(width / 2.0f, height / 2.0f);
			m_origRects.push_back(Rect(leftBottom, rightTop));
			m_rectColors.push_back(Color(MathUtil::getRandom(), MathUtil::getRandom(), MathUtil::getRandom()));
		}
	}

	void BinPackingVisualizer::renderDebug()
	{
		std::vector<Rect> lastBinRects = m_packedRects.empty() ? std::vector<Rect>() : m_packedRects.back();
		for (unsigned int i = 0; i < lastBinRects.size(); i++)
			DebugUtil::drawSolidRect(lastBinRects[i], m_rectColors[i]);

		std::vector<Rect> partitionBuffer = BinPacking::getPartitionBuffer();
		for (unsigned int i = 0; i < partitionBuffer.size(); i++)
			DebugUtil::drawRect(partitionBuffer[i], Color::Green);
	}

	void BinPackingVisualizer::update()
	{
		if(InputManager::getInstance()->isKeyGoingDown(KeyCode::Return))
		{ 
			m_currentStep++;
			m_currentStep = std::min(m_currentStep, m_origRects.size());
			m_packedRects = BinPacking::calculate(BIN, m_origRects, m_currentStep);
		}
	}
}
