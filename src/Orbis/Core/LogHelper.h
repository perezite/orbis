#pragma once

#include <string>

namespace Core
{
	class LogHelper
	{
	public:
		// log a message
		static void LogMessage(const char* fmt, ...);

		// show a message box
		static void ShowMessageBox(std::string message, std::string title);
	};
}