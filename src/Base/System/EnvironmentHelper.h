#pragma once

#include <string>

namespace System
{
	class EnvironmentHelper
	{
	public:
		// get the path of the directory the exectuable resides in
		static std::string GetExecutableDirectoryPath();

		// check whether we are on a mobile platform
		static bool IsMobile();
	public:
		static const std::string PathSeparator;
	};
}