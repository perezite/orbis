#pragma once

#include <string>

namespace System
{
	class EnvironmentHelper
	{
	public:
		// get the path of the directory the exectuable resides in
		static std::string GetExecutableDirectoryPath();

	public:
		static const std::string PathSeparator;
	};
}