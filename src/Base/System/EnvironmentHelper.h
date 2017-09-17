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

		// combine file oder folder path
		static std::string EnvironmentHelper::CombinePath(std::vector<std::string> parts);

	public:
		static const std::string PathSeparator;
	};
}