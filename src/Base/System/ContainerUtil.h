#pragma once

#include <vector>
#include <algorithm>

namespace base
{
	class ContainerUtil
	{
	public:
		template <class T>
		static std::vector<std::vector<T>> group(std::vector<T> elements, bool (*comparer)(T , T))
		{
			std::vector<std::vector<T>> groups;

			for (unsigned int i = 0; i < elements.size(); i++)
			{
				bool found = false;

				for (unsigned int j = 0; j < groups.size(); j++)
				{
					if (comparer(elements[i], (groups[j])[0]))
					{
						groups[j].push_back(elements[i]);
						found = true;
						break;
					}
				}

				if (!found)
				{
					std::vector<T> newGroup;
					newGroup.push_back(elements[i]);
					groups.push_back(newGroup);
				}
			}

			return groups;
		}
	};
}