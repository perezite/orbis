#include "StringHelper.h"

#include <stdarg.h>
#include <stdlib.h>
#include <memory.h>
#include <string>
#include <iostream>
#include <sstream>
#include <iostream>
#include <iomanip>

namespace System
{
	std::string StringHelper::getFormatted(std::string format, int maximalFormattedLength, ...)
	{
		va_list args;
		va_start(args, maximalFormattedLength);
		std::string result = getFormatted(format, maximalFormattedLength, args);
		va_end(args);

		return result;
	}

	std::string StringHelper::getFormatted(std::string format, ...)
	{
		va_list args;

		va_start(args, format);
		std::string result = getFormatted(format, DefaultMaximalFormattedLength, args);
		va_end(args);

		return result;
	}

	std::string StringHelper::getFormatted(std::string format, int maximalFormattedLength, va_list args)
	{
		char *buffer = (char*)malloc(sizeof(char) * (maximalFormattedLength + 1));

		vsnprintf(buffer, maximalFormattedLength, format.c_str(), args);

		std::string result = std::string(buffer);
		free(buffer);

		return result;
	}

	bool StringHelper::isEmpty(std::string str)
	{
		return str == "";
	}

	std::string StringHelper::load(float val, int precision)
	{
		std::stringstream ss;
		ss << std::fixed << std::setprecision(precision) << val << "f";
		std::string result = ss.str();
		return result;
	}

	bool StringHelper::seek(std::istringstream& is, char c)
	{
		char r;
		while (is.get(r) && c != r);

		if (r != c)
			return false;

		return true;
	}

	std::string StringHelper::read(std::istringstream& is, char d)
	{
		std::string buf;
		char r;
		while (is.get(r) && r != d)
			buf.push_back(r);

		return buf;
	}
}