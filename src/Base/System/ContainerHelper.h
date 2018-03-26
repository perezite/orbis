#pragma once

namespace System
{
	class ContainerHelper 
	{
	public: 
		// insert the values in the values vector at the end of the target vector
		template <class T>
		static void AddRange(std::vector<T> target, std::vector<T> values)
		{
			for (unsigned int i = 0; i < values.size(); i++) {
				target.push_back(values[i]);
			}
		}
	};
}