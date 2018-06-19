#pragma once

#include <string>

namespace Core
{
	class LogHelper
	{
	public:
		// log a message
		static void logMessage(const char* fmt, ...);

		// show a message box
		static void showMessageBox(std::string message, std::string title);
	};
}