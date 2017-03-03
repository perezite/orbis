#include "StringHelper.h"
#include "PlatformHelper.h"

#include <cstdarg>
#include <stdlib.h>
#include <string>
#include <memory.h>
#include <iostream>

namespace System
{
	std::string StringHelper::GetFormattedString(std::string format, int maximalFormattedLength, ...)
	{
		orbis_va_list args;
		va_start(args, maximalFormattedLength);
		std::string result = GetFormattedString(format, maximalFormattedLength, args);
		va_end(args);

		return result;
	}

	std::string StringHelper::GetFormattedString(std::string format, ...)
	{
		orbis_va_list args;

		va_start(args, format);
		std::string result = GetFormattedString(format, DefaultMaximalFormattedLength, args);
		va_end(args);

		return result;
	}

	std::string StringHelper::GetFormattedString(std::string format, int maximalFormattedLength, orbis_va_list args)
	{
		char *buffer = (char*)malloc(sizeof(char) * (maximalFormattedLength + 1));

		vsnprintf(buffer, maximalFormattedLength, format.c_str(), args);

		std::string result = std::string(buffer);
		free(buffer);

		return result;
	}
}