#pragma once

#include <vector>

namespace System
{
	class MemoryHelper
	{
	public:
		template <class T>
		static void Delete(T* pointer)
		{
			if (pointer)
				delete pointer;
			pointer = NULL;
		}

		template <class T>
		static void Remove(std::vector<T*>& vec, unsigned int index)
		{
			T* pointer = vec.at(index);
			Delete(pointer);
			vec.erase(vec.begin() + index);
		}

		template <class T>
		static void Clear(std::vector<T*>& vec)
		{
			for (unsigned int i = 0; i < vec.size(); i++)
			{
				T* pointer = vec.at(i);
				delete pointer;
			}

			vec.clear();
		}
	};
}