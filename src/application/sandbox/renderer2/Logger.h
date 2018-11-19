#pragma once

#include <sstream>
#include <iostream>
#include <stdlib.h>

namespace sb
{
	namespace renderer2
	{
		class Logger
		{
		public:
			virtual ~Logger()
			{
				std::cout << m_errorStream.str();
				std::cin.get();
				#if defined(_DEBUG) && defined(WIN32)
					__debugbreak();
				#endif
			}

			std::ostream& error() { return m_errorStream; }

		private:
			std::ostringstream m_errorStream;
		};
	}
}