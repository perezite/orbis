#pragma once

#include <SDL2/SDL.h>

#include <sstream>
#include <iostream>

namespace orb
{
	class Log
	{
	public:
		std::ostream& message() { return m_message; }

		std::ostream& error() { return m_error; }

		std::ostream& errorMessageBox(std::string messageBoxTitle) { 
			m_errorMessageBoxTitle = messageBoxTitle; 
			return m_errorMessageBox; 
		}

		virtual ~Log()
		{
			std::string str = m_message.str();
			if (str.length() > 0)
				SDL_Log("%s", str.c_str());

			str = m_error.str();
			if (str.length() > 0)
				SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s", str.c_str());

			str = m_errorMessageBox.str();
			if (str.length() > 0)
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, m_errorMessageBoxTitle.c_str(), str.c_str(), NULL);
		}

	private:
		std::ostringstream m_message;

		std::ostringstream m_error;

		std::string m_errorMessageBoxTitle;
		
		std::ostringstream m_errorMessageBox;
	};
}