#pragma once

#include <string>

namespace Core
{
	class LogHelper
	{
	public:
		static void LogMessage(const char* fmt, ...);
	};
}