#include "BinPacking.h"

#include "../System/Exception.h"
using namespace System;

#include <algorithm>

namespace Algorithms
{
	std::vector<Rect> BinPacking::m_partitionBuffer;


	std::vector<Rect> BinPacking::Execute(Rect bin, std::vector<Rect> origRects)
	{
		return Execute(bin, origRects, origRects.size());
	}

	std::vector<Rect> BinPacking::Execute(Rect bin, std::vector<Rect> origRects, unsigned int maxSteps)
	{
		std::vector<Rect> rects = origRects;
		m_partitionBuffer.clear();

		// 1) sort rects by their area
		SortRectsByArea(rects);

		// 2) initialize the list of (empty) partitions with the unpartitioned bin
		std::vector<Rect> partitions{ bin };
		m_partitionBuffer.push_back(bin);

		for (unsigned int i = 0; i < maxSteps; i++)
		{
			// 3a) find smallest fitting partition for current rect
			unsigned int partitionIdx = FindSmallestFittingPartition(partitions, rects[i]);

			// 3b) move the rect to the bottom left corner of the selected partition
			TranslateRect(rects[i], partitions[partitionIdx].leftBottom);

			// 3c) split the current partition into two parts
			std::tuple<Rect, Rect> subPartitions = Split(partitions[partitionIdx], rects[i]);

			// 4c) remove the orginal partitions, then add the sub-partitions 
			partitions.erase(partitions.begin() + partitionIdx);
			partitions.push_back(std::get<0>(subPartitions));
			partitions.push_back(std::get<1>(subPartitions));

			// store the new partitions for further visualization
			m_partitionBuffer.push_back(std::get<0>(subPartitions));
			m_partitionBuffer.push_back(std::get<1>(subPartitions));
		}

		return rects;
	}

	void BinPacking::SortRectsByArea(std::vector<Rect>& rects)
	{
		std::vector<Rect> sorted;
		for (unsigned int i = 0; i < rects.size(); i++)
		{
			unsigned int j;
			for (j = 0; j < sorted.size(); j++)
			{
				if (rects[i].GetArea() >= sorted[j].GetArea())
					break;
			}
			sorted.insert(sorted.begin() + j, rects[i]);
		}

		rects = sorted;
	}

	unsigned int BinPacking::FindSmallestFittingPartition(std::vector<Rect> partitions, Rect rect)
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

	void BinPacking::TranslateRect(Rect& rect, Vector2D leftBottomTargetPos)
	{
		Vector2D dist = leftBottomTargetPos - rect.leftBottom;

		rect.leftBottom += dist;
		rect.rightTop += dist;
	}

	std::tuple<Rect, Rect> BinPacking::Split(Rect partition, Rect rect)
	{
		bool splitVertical = rect.GetWidth() > rect.GetHeight();
		Rect smallerBin; Rect largerBin;

		if (splitVertical)
		{
			smallerBin = Rect(rect.GetRight(), partition.GetBottom(),
				partition.GetRight(), rect.GetTop());
			largerBin = Rect(partition.GetLeft(), rect.GetTop(),
				partition.GetRight(), partition.GetTop());
		}
		else
		{
			smallerBin = Rect(partition.GetLeft(), rect.GetTop(),
				rect.GetRight(), partition.GetTop());
			largerBin = Rect(rect.GetRight(), partition.GetBottom(),
				partition.GetRight(), partition.GetTop());
		}

		return std::make_tuple(smallerBin, largerBin);
	}
}