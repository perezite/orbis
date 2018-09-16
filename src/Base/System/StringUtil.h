#pragma once

#include <stdlib.h>
#include <string>

namespace base
{
	namespace system
	{
		class StringUtil
		{
		public:
			// get formatted string 
			static std::string getFormatted(std::string format, int maximalFormattedLength, ...);

			// get formatted string
			static std::string getFormatted(std::string format, ...);


		protected:
			// get formatted string
			static std::string getFormatted(std::string format, int maximalFormattedLength, va_list args);

		private:
			// default maximal length of formatted string
			static const int DefaultMaximalFormattedLength = 1024;
		};
	}
}