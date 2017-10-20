#include "LogHelper.h"

#include "../Libraries/SDL.h"
using namespace Libraries;

#include <stdarg.h>

namespace Core
{
	void LogHelper::LogMessage(const char* fmt, ...)
	{
		va_list args; 

		va_start(args, fmt);
			SDL::Log(fmt, args);
		va_end(args);
	}

	void LogHelper::ShowMessageBox(std::string message, std::string title)
	{
		SDL::ShowSimpleMessageBox(message.c_str(), title.c_str());
	}
}