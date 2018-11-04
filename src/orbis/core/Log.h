#pragma once

#include <sstream>
#include <iostream>

namespace orb
{
	class Log
	{
	public:
		std::ostream& message() { return m_message; }

		std::ostream& error() { return m_error; }

		virtual ~Log()
		{
			std::cout << m_message.str();
			std::cerr << m_error.str();
		}

	private:
		std::ostringstream m_message;

		std::ostringstream m_error;
	};
}