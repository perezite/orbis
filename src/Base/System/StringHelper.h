#pragma once

#include <stdlib.h>
#include <string>

namespace System
{
	class StringHelper
	{
	public:
		// get formatted string 
		static std::string GetFormattedString(std::string format, int maximalFormattedLength, ...);

		// get formatted string
		static std::string GetFormattedString(std::string format, ...);

		// is the string empty
		static bool IsEmpty(std::string str);

	protected:
		// get formatted string
		static std::string GetFormattedString(std::string format, int maximalFormattedLength, va_list args);

	private:
		// default maximal length of formatted string
		static const int DefaultMaximalFormattedLength = 1024;
	};
}