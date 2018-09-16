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

			// is the string empty
			static bool isEmpty(std::string str);

			// convert to string
			static std::string toJson(float val, int precision = 5);

			// seek the next occurence of c in is
			static bool seek(std::istringstream& is, char c);

			// read into buf until the next occurence of the delimiter d in is. The occurence of d is skipped and not written to buf. 
			static std::string read(std::istringstream& is, char d);

		protected:
			// get formatted string
			static std::string getFormatted(std::string format, int maximalFormattedLength, va_list args);

		private:
			// default maximal length of formatted string
			static const int DefaultMaximalFormattedLength = 1024;
		};
	}
}