#include "LogUtil.h"

#include "../Libraries/SDL.h"

#include <stdarg.h>

namespace orb
{
	void LogUtil::logMessage(const char* fmt, ...)
	{
		static char buf[1024];
		va_list args;

		va_start(args, fmt);
		vsnprintf(buf, 1024, fmt, args);
		SDL_Log("%s", buf);
		va_end(args);

	}

	void LogUtil::showMessageBox(std::string message, std::string title)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title.c_str(), message.c_str(), NULL);
	}
}