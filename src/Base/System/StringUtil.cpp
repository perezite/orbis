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

	std::vector<std::string> StringUtil::split(const std::string str, const std::string delim)
	{
		std::string temp = str;
		std::vector<std::string> result;
		std::string current;

		size_t pos = 0;
		while ((pos = temp.find(delim)) != std::string::npos) 
		{
			current = temp.substr(0, pos);
			temp.erase(0, pos + delim.length());
			result.push_back(current);
		}

		result.push_back(temp);

		return result;
	}

	bool StringUtil::startsWith(std::string str, std::string start)
	{
		return str.find(start) == 0;
	}


	std::string StringUtil::remove(std::string str, std::vector<std::string> substrs)
	{
		std::string result = str;

		unsigned int pos = std::string::npos;
		for (unsigned int i = 0; i < substrs.size(); i++)
			while ((pos = result.find(substrs[i])) != std::string::npos)
				result.erase(pos, substrs[i].length());

		return result;
	}
}


