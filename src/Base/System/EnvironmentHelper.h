#pragma once

#include <string>
#include <vector>

namespace System
{
	class EnvironmentHelper
	{
	public:
		// get the path of the directory the exectuable resides in
		static std::string GetExecutableDirectoryPath();

		// check whether we are on a mobile platform
		static bool IsMobile();

		// combine file or folder paths
		static std::string CombinePath(std::vector<std::string> parts);

		// write a string to the systems's clipboard
		static void WriteToClipboard(std::string value);

	public:
		static const std::string PathSeparator;
	};
}