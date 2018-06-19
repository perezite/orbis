#include "BinPackingVisualizer.h"

#include "../../Base/Math/MathHelper.h"
#include "../../Base/Algorithms/BinPacking.h"
using namespace Math;
using namespace Algorithms;

#include "../../Orbis/Core/DebugHelper.h"
#include "../../Orbis/Input/InputManager.h"
using namespace Core;
using namespace Input;

#include <iostream>
#include <limits>
#include <algorithm>

namespace Controllers
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
			float width = MathHelper::GetRandom(EXTENTS_RANGE.min, EXTENTS_RANGE.max);
			float height = MathHelper::GetRandom(EXTENTS_RANGE.min, EXTENTS_RANGE.max);
			Vector2D leftBottom(-width / 2.0f, -height / 2.0f);
			Vector2D rightTop(width / 2.0f, height / 2.0f);
			m_origRects.push_back(Rect(leftBottom, rightTop));
			m_rectColors.push_back(Color(MathHelper::GetRandom(), MathHelper::GetRandom(), MathHelper::GetRandom()));
		}
	}

	void BinPackingVisualizer::RenderDebug()
	{
		std::vector<Rect> lastBinRects = m_packedRects.empty() ? std::vector<Rect>() : m_packedRects.back();
		for (unsigned int i = 0; i < lastBinRects.size(); i++)
			DebugHelper::DrawSolidRect(lastBinRects[i], m_rectColors[i]);

		std::vector<Rect> partitionBuffer = BinPacking::GetPartitionBuffer();
		for (unsigned int i = 0; i < partitionBuffer.size(); i++)
			DebugHelper::DrawRect(partitionBuffer[i], Color::Green);
	}

	void BinPackingVisualizer::Update()
	{
		if(InputManager::getInstance()->IsKeyGoingDown(KeyCode::Return))
		{ 
			m_currentStep++;
			m_currentStep = std::min(m_currentStep, m_origRects.size());
			m_packedRects = BinPacking::Execute(BIN, m_origRects, m_currentStep);
		}
	}
}
