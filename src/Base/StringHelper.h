#pragma once

#include <stdarg.h>
#include <string>

class StringHelper
{
public:
	static std::string GetFormattedString(std::string format, int maximalFormattedLength, ...);

	static std::string GetFormattedString(std::string format, ...);

protected: 
	static std::string GetFormattedString(std::string format, int maximalFormattedLength, va_list args);

private:
	static const int DefaultMaximalFormattedLength = 1024;
};