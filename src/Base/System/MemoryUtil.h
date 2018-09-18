#pragma once

#include <vector>

namespace base
{
	class MemoryUtil
	{
	public:
		template <class T>
		static void remove(std::vector<T*>& vec, unsigned int index)
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