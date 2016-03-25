#pragma once

#include <string>

namespace Core
{
	class StringHelper
	{
	public:
		static std::string GetFormattedString(std::string format, int maximalFormattedLength, ...);

		static std::string GetFormattedString(std::string format, ...);

	protected:
		static std::string GetFormattedString(std::string format, int maximalFormattedLength, va_list args);

	private:
		static const int DefaultMaximalFormattedLength = 1024;
	};
}