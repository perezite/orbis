#pragma once

#include <string>
#include <vector>

namespace base
{
	namespace system
	{
		class EnvironmentUtil
		{
		public:
			// get the path of the directory the exectuable resides in
			static std::string getExecutableDirectoryPath();

			// check whether we are on a mobile platform
			static bool isMobile();

			// combine file or folder paths
			static std::string combinePath(std::vector<std::string> parts);

			// write a string to the systems's clipboard
			static void writeToClipboard(std::string value);

		public:
			static const std::string PathSeparator;
		};
	}
}