#include "BinPacking.h"

#include "../System/Exception.h"
#include "../Math/MathHelper.h"
using namespace System;
using namespace Math;

#include <algorithm>

namespace Algorithms
{
	std::vector<Rect> BinPacking::m_partitionBuffer;

	std::vector<std::vector<Rect>> BinPacking::Execute(Rect bin, std::vector<Rect> rects)
	{
		return Execute(bin, rects, rects.size());
	}

	std::vector<std::vector<Rect>> BinPacking::Execute(Rect bin, std::vector<Rect> rects, unsigned int numSteps)
	{
		std::vector<std::vector<Rect>> packedRects;

		while (numSteps > 0)
		{
			std::vector<Rect> currentPackedRects = Pack(bin, rects, numSteps);
			packedRects.push_back(currentPackedRects);
			numSteps -= currentPackedRects.size();
		}

		return packedRects;
	}

	std::vector<Rect> BinPacking::Pack(Rect bin, std::vector<Rect>& rects, unsigned int numSteps)
	{
		std::vector<Rect> packedRects;
		m_partitionBuffer.clear();

		// 1) sort rects by their area
		SortRectsByArea(rects);

		// 2) initialize the list of (empty) partitions with the unpartitioned bin
		std::vector<Rect> partitions{ bin };
		m_partitionBuffer.push_back(bin);

		for (unsigned int i = 0; i < numSteps; i++)
		{
			Rect& currentRect = rects[0];

			// 3a) find smallest fitting partition for current rect
			int partitionIdx = FindSmallestFittingPartition(partitions, currentRect);

			// 3b) if no fitting rect was found, the bin is full and we are done
			if (partitionIdx == -1)
				break;

			// 3c) move the rect to the bottom left corner of the selected partition
			TranslateRect(currentRect, partitions[partitionIdx].leftBottom);

			// 3d) split the current partition into two parts
			std::tuple<Rect, Rect> subPartitions = Split(partitions[partitionIdx], currentRect);

			// 3e) remove the orginal partition, then add the sub-partitions 
			partitions.erase(partitions.begin() + partitionIdx);
			partitions.push_back(std::get<0>(subPartitions));
			partitions.push_back(std::get<1>(subPartitions));

			// store the new partitions for further visualization
			m_partitionBuffer.push_back(std::get<0>(subPartitions));
			m_partitionBuffer.push_back(std::get<1>(subPartitions));

			packedRects.push_back(currentRect);
			rects.erase(rects.begin());
		}

		return packedRects;
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

	int BinPacking::FindSmallestFittingPartition(std::vector<Rect> partitions, Rect rect)
	{
		float minArea = std::numeric_limits<float>::max();
		int smallest = -1;

		for (unsigned int i = 0; i < partitions.size(); i++)
		{
			float eps = 0.001f;
			if (rect.GetWidth() < (partitions[i].GetWidth() + eps) && rect.GetHeight() < (partitions[i].GetHeight() + eps))
			{
				if (partitions[i].GetArea() < minArea)
				{
					smallest = i;
					minArea = partitions[i].GetArea();
				}
			}
		}

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
