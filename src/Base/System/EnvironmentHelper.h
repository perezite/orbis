#pragma once

#include <string>

namespace System
{
	class EnvironmentHelper
	{
	public:
		// get the current working directory
		static std::string GetWorkingDirectory();

		// get the path of the directory the exectuable resides in
		static std::string GetExecutableDirectoryPath();

		// set the working direcotry
		static void SetWorkingDirectory(std::string workingDirectoryPath);

		// get the path separator
		static std::string GetPathSeparator();
	};
}