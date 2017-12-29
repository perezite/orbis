#include "BinPackingVisualizer.h"

#include "../../Base/Math/MathHelper.h"
#include "../../Base/System/Exception.h"
using namespace Math;
using namespace System;

#include "../../Orbis/Core/DebugHelper.h"
using namespace Core;

#include <iostream>
#include <limits>

namespace Controllers
{
	// number of rects
	const unsigned int BinPackingVisualizer::NUM_RECTS = 14;

	// the range for generated extents
	const Range BinPackingVisualizer::EXTENTS_RANGE(0.1f, 0.2f);

	BinPackingVisualizer::BinPackingVisualizer()
		: m_bin(-0.5f, -0.5f, 0.5f, 0.5f)
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

		Pack();
	}

	void BinPackingVisualizer::Render()
	{
		for (unsigned int i = 0; i < m_rects.size(); i++)
		{
			DebugHelper::DrawSolidRect(m_rects[i], m_rectColors[i]);
		}
	}

	void BinPackingVisualizer::Pack()
	{
		// 1) sort rects by their area
		SortRectsByArea();

		// 2) initialize the list of (empty) partitions with the unpartitioned bin
		std::vector<Rect> partitions { m_bin };

		for (unsigned int i = 0; i < m_rects.size(); i++)
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
				if (m_rects[i].GetArea() <= sorted[j].GetArea())
					break;
			}
			sorted.insert(sorted.begin() + j, m_rects[i]);
		}

		m_rects = sorted;
	}

	unsigned int BinPackingVisualizer::FindSmallestFittingPartition(std::vector<Rect> m_partitions, Rect rect)
	{
		float minArea = std::numeric_limits<float>::max();
		int smallest = -1;

		for (unsigned int i = 0; i < m_partitions.size(); i++)
		{
			if (rect.GetWidth() < m_partitions[i].GetWidth() && rect.GetHeight() < m_partitions[i].GetHeight())
			{
				if (m_partitions[i].GetArea() < minArea)
				{
					smallest = i;
					minArea = m_partitions[i].GetArea();
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
