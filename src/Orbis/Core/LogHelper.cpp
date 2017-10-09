#include "LogHelper.h"

#include "SDL2/SDL.h"

#include <stdarg.h>

namespace Core
{
	void LogHelper::LogMessage(const char* fmt, ...)
	{
		std::string message(fmt);
		message = "Message: " + message;

		va_list args; 
		va_start(args, fmt);
		SDL_Log(message.c_str(), args);
		va_end(args);
	}

	void LogHelper::ShowMessageBox(std::string message, std::string title)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title.c_str(), message.c_str(), NULL);
	}
}