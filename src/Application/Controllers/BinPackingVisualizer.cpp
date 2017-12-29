#include "BinPackingVisualizer.h"

#include "../../Base/Math/MathHelper.h"
#include "../../Base/System/Exception.h"
using namespace Math;
using namespace System;

#include "../../Orbis/Core/DebugHelper.h"
#include "../../Orbis/Input/InputManager.h"
using namespace Core;
using namespace Input;

#include <iostream>
#include <limits>
#include <algorithm>

namespace Controllers
{
	// number of rects
	const unsigned int BinPackingVisualizer::NUM_RECTS = 33;

	// the range for generated extents
	const Range BinPackingVisualizer::EXTENTS_RANGE(0.1f, 0.2f);

	BinPackingVisualizer::BinPackingVisualizer()
		: m_bin(-0.5f, -0.5f, 0.5f, 0.5f), m_currentStep(0)
	{
		// insert rects and colors
		for (unsigned int i = 0; i < NUM_RECTS; i++)
		{
			float width = MathHelper::GetRandom(EXTENTS_RANGE.min, EXTENTS_RANGE.max);
			float height = MathHelper::GetRandom(EXTENTS_RANGE.min, EXTENTS_RANGE.max);
			Vector2D leftBottom(-width / 2.0f, -height / 2.0f);
			Vector2D rightTop(width / 2.0f, height / 2.0f);
			m_rects.push_back(Rect(leftBottom, rightTop));
			m_rectColors.push_back(Color(MathHelper::GetRandom(), MathHelper::GetRandom(), MathHelper::GetRandom()));
		}
	}

	void BinPackingVisualizer::Render()
	{
		for (unsigned int i = 0; i < m_currentStep; i++)
			DebugHelper::DrawSolidRect(m_rects[i], m_rectColors[i]);

		for (unsigned int i = 0; i < m_partitionBuffer.size(); i++)
			DebugHelper::DrawRect(m_partitionBuffer[i], Color::Green);
	}

	void BinPackingVisualizer::Update()
	{
		if(InputManager::GetInstance()->IsKeyGoingDown(KeyCode::Return))
		{ 
			m_currentStep++;
			m_currentStep = std::min(m_currentStep, m_rects.size());
			Pack(m_currentStep);
		}
	}

	void BinPackingVisualizer::Pack(unsigned int maxStep)
	{
		m_partitionBuffer.clear();

		// 1) sort rects by their area
		SortRectsByArea();

		// 2) initialize the list of (empty) partitions with the unpartitioned bin
		std::vector<Rect> partitions { m_bin };
		m_partitionBuffer.push_back(m_bin);

		for (unsigned int i = 0; i < maxStep; i++)
		{
			// 3a) find smallest fitting partition for current rect
			unsigned int partitionIdx = FindSmallestFittingPartition(partitions, m_rects[i]);

			// 3b) move the rect to the bottom left corner of the selected partition
			TranslateRect(m_rects[i], partitions[partitionIdx].leftBottom);

			// 3c) split the current partition into two parts
			std::tuple<Rect, Rect> rects = Split(partitions[partitionIdx], m_rects[i]);
			
			// 4c) remove the orginal partitions, then add the sub-partitions 
			partitions.erase(partitions.begin() + partitionIdx);
			partitions.push_back(std::get<0>(rects));
			partitions.push_back(std::get<1>(rects));

			// store the new partitions for further visualization
			m_partitionBuffer.push_back(std::get<0>(rects));
			m_partitionBuffer.push_back(std::get<1>(rects));

		}
	}

	void BinPackingVisualizer::SortRectsByArea()
	{
		std::vector<Rect> sorted;
		for (unsigned int i = 0; i < m_rects.size(); i++)
		{
			unsigned int j;
			for (j = 0; j < sorted.size(); j++)
			{
				if (m_rects[i].GetArea() >= sorted[j].GetArea())
					break;
			}
			sorted.insert(sorted.begin() + j, m_rects[i]);
		}

		m_rects = sorted;
	}

	unsigned int BinPackingVisualizer::FindSmallestFittingPartition(std::vector<Rect> partitions, Rect rect)
	{
		float minArea = std::numeric_limits<float>::max();
		int smallest = -1;

		for (unsigned int i = 0; i < partitions.size(); i++)
		{
			if (rect.GetWidth() < partitions[i].GetWidth() && rect.GetHeight() < partitions[i].GetHeight())
			{
				if (partitions[i].GetArea() < minArea)
				{
					smallest = i;
					minArea = partitions[i].GetArea();
				}
			}
		}

		Exception::Assert(smallest > -1, "The given rects exceed the pack space in the bin");

		return smallest;
	}

	void BinPackingVisualizer::TranslateRect(Rect & rect, Vector2D leftBottomTargetPos)
	{
		Vector2D dist = leftBottomTargetPos - rect.leftBottom;

		rect.leftBottom += dist;
		rect.rightTop += dist;
	}

	std::tuple<Rect, Rect> BinPackingVisualizer::Split(Rect partition, Rect rect)
	{
		bool splitVertical = rect.GetWidth() > rect.GetHeight();
		Rect smallerBin; Rect largerBin;

		if (splitVertical)
		{
			smallerBin = Rect(	rect.GetRight(), partition.GetBottom(),
								partition.GetRight(), rect.GetTop());
			largerBin = Rect(	partition.GetLeft(), rect.GetTop(),
								partition.GetRight(), partition.GetTop());
		}
		else
		{
			smallerBin = Rect(	partition.GetLeft(), rect.GetTop(),
								rect.GetRight(), partition.GetTop());
			largerBin = Rect(	rect.GetRight(), partition.GetBottom(),
								partition.GetRight(), partition.GetTop());
		}

		return std::make_tuple(smallerBin, largerBin);
	}
}
