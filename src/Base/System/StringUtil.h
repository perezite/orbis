#pragma once

#include <stdlib.h>
#include <string>
#include <vector>

namespace base
{
	class StringUtil
	{
	public:
		// get formatted string 
		static std::string getFormatted(std::string format, int maximalFormattedLength, ...);

		// get formatted string
		static std::string getFormatted(std::string format, ...);

		// get a split string
		static std::vector<std::string> split(const std::string str, const std::string delimiter);

		// check if string starts with given string
		static bool startsWith(std::string str, std::string start);

		// join several strings together
		template <class T>
		static std::string join(std::vector<T> elems, std::string delim);

		// remove substrings from string
		static std::string remove(std::string str, std::vector<std::string> substrs);

	protected:
		// get formatted string
		static std::string getFormatted(std::string format, int maximalFormattedLength, va_list args);

	private:
		// default maximal length of formatted string
		static const int DefaultMaximalFormattedLength = 1024;
	};

	template <class T>
	std::string StringUtil::join(std::vector<T> elems, std::string delim)
	{
		std::ostringstream os;
		for (unsigned int i = 0; i < elems.size(); i++) {
			os << elems[i];
			if (i < elems.size() - 1)
				os << delim;
		}
		return os.str();
	}
}