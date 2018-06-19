#pragma once

#include <vector>

namespace System
{
	class MemoryHelper
	{
	public:
		template <class T>
		static void Remove(std::vector<T*>& vec, unsigned int index)
		{
			delete vec[index];
			vec.erase(vec.begin() + index);
		}

		template <class T>
		static void clear(std::vector<T*>& vec)
		{
			for (unsigned int i = 0; i < vec.size(); i++)
				delete vec[i];
			vec.clear();
		}
	};
}