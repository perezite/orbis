#include "StringUtil.h"

#include <stdarg.h>
#include <stdlib.h>
#include <memory.h>
#include <string>
#include <iostream>
#include <sstream>
#include <iostream>
#include <iomanip>

namespace base
{
	std::string StringUtil::getFormatted(std::string format, int maximalFormattedLength, ...)
	{
		va_list args;
		va_start(args, maximalFormattedLength);
		std::string result = getFormatted(format, maximalFormattedLength, args);
		va_end(args);

		return result;
	}

	std::string StringUtil::getFormatted(std::string format, ...)
	{
		va_list args;

		va_start(args, format);
		std::string result = getFormatted(format, DefaultMaximalFormattedLength, args);
		va_end(args);

		return result;
	}

	std::string StringUtil::getFormatted(std::string format, int maximalFormattedLength, va_list args)
	{
		char *buffer = (char*)malloc(sizeof(char) * (maximalFormattedLength + 1));

		vsnprintf(buffer, maximalFormattedLength, format.c_str(), args);

		std::string result = std::string(buffer);
		free(buffer);

		return result;
	}
}