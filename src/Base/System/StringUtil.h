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
		static std::string join(std::vector<std::string> elems, std::string delimiter);

	protected:
		// get formatted string
		static std::string getFormatted(std::string format, int maximalFormattedLength, va_list args);

	private:
		// default maximal length of formatted string
		static const int DefaultMaximalFormattedLength = 1024;
	};
}