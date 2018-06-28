#include "BinPacking.h"

#include "../System/Exception.h"
#include "../Math/MathHelper.h"
using namespace base::system;
using namespace base::math;

#include <algorithm>

namespace base
{
	namespace algorithms
	{
		std::vector<Rect> BinPacking::m_partitionBuffer;

		std::vector<std::vector<Rect>> BinPacking::calculate(Rect bin, std::vector<Rect> rects)
		{
			return calculate(bin, rects, rects.size());
		}

		std::vector<std::vector<Rect>> BinPacking::calculate(Rect bin, std::vector<Rect> rects, unsigned int numSteps)
		{
			std::vector<std::vector<Rect>> packedRects;

			while (numSteps > 0)
			{
				std::vector<Rect> currentPackedRects = pack(bin, rects, numSteps);
				packedRects.push_back(currentPackedRects);
				numSteps -= currentPackedRects.size();
			}

			return packedRects;
		}

		std::vector<Rect> BinPacking::pack(Rect bin, std::vector<Rect>& rects, unsigned int numSteps)
		{
			std::vector<Rect> packedRects;
			m_partitionBuffer.clear();

			// 1) sort rects by their area
			sortRectsByArea(rects);

			// 2) initialize the list of (empty) partitions with the unpartitioned bin
			std::vector<Rect> partitions{ bin };
			m_partitionBuffer.push_back(bin);

			for (unsigned int i = 0; i < numSteps; i++)
			{
				Rect& currentRect = rects[0];

				// 3a) find smallest fitting partition for current rect
				int partitionIdx = findSmallestFittingPartition(partitions, currentRect);

				// 3b) if no fitting rect was found, the bin is full and we are done
				if (partitionIdx == -1)
					break;

				// 3c) move the rect to the bottom left corner of the selected partition
				translateRect(currentRect, partitions[partitionIdx].leftBottom);

				// 3d) split the current partition into two parts
				std::tuple<Rect, Rect> subPartitions = split(partitions[partitionIdx], currentRect);

				// 3e) remove the orginal partition, then add the sub-partitions 
				partitions.erase(partitions.begin() + partitionIdx);
				partitions.push_back(std::get<0>(subPartitions));
				partitions.push_back(std::get<1>(subPartitions));

				// 3f) store the new partitions for further visualization
				m_partitionBuffer.push_back(std::get<0>(subPartitions));
				m_partitionBuffer.push_back(std::get<1>(subPartitions));

				packedRects.push_back(currentRect);
				rects.erase(rects.begin());
			}

			return packedRects;
		}

		void BinPacking::sortRectsByArea(std::vector<Rect>& rects)
		{
			std::vector<Rect> sorted;
			for (unsigned int i = 0; i < rects.size(); i++)
			{
				unsigned int j;
				for (j = 0; j < sorted.size(); j++)
				{
					if (rects[i].getArea() >= sorted[j].getArea())
						break;
				}
				sorted.insert(sorted.begin() + j, rects[i]);
			}

			rects = sorted;
		}

		int BinPacking::findSmallestFittingPartition(std::vector<Rect> partitions, Rect rect)
		{
			float minArea = std::numeric_limits<float>::max();
			int smallest = -1;

			for (unsigned int i = 0; i < partitions.size(); i++)
			{
				float eps = 0.001f;
				if (rect.getWidth() < (partitions[i].getWidth() + eps) && rect.getHeight() < (partitions[i].getHeight() + eps))
				{
					if (partitions[i].getArea() < minArea)
					{
						smallest = i;
						minArea = partitions[i].getArea();
					}
				}
			}

			return smallest;
		}

		void BinPacking::translateRect(Rect& rect, Vector2D leftBottomTargetPos)
		{
			Vector2D dist = leftBottomTargetPos - rect.leftBottom;

			rect.leftBottom += dist;
			rect.rightTop += dist;
		}

		std::tuple<Rect, Rect> BinPacking::split(Rect partition, Rect rect)
		{
			bool splitVertical = rect.getWidth() > rect.getHeight();
			Rect smallerBin; Rect largerBin;

			if (splitVertical)
			{
				smallerBin = Rect(rect.getRight(), partition.getBottom(),
					partition.getRight(), rect.getTop());
				largerBin = Rect(partition.getLeft(), rect.getTop(),
					partition.getRight(), partition.getTop());
			}
			else
			{
				smallerBin = Rect(partition.getLeft(), rect.getTop(),
					rect.getRight(), partition.getTop());
				largerBin = Rect(rect.getRight(), partition.getBottom(),
					partition.getRight(), partition.getTop());
			}

			return std::make_tuple(smallerBin, largerBin);
		}
	}
}