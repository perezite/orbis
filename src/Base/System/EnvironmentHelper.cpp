#include "EnvironmentHelper.h"

#include "Exception.h"
#include "StringHelper.h"

#ifdef WIN32
	#include <windows.h>
	#include <direct.h>
#endif

#include <string>

namespace System
{
	const std::string EnvironmentHelper::PathSeparator = "\\";

	std::string System::EnvironmentHelper::GetExecutableDirectoryPath()
	{
		#ifdef WIN32
			wchar_t filePath[MAX_PATH];

			// get executable file path
			HMODULE hModule = GetModuleHandle(NULL);
			if (hModule == NULL)
				throw Exception("GetModuleHandle() failed");
			GetModuleFileName(hModule, filePath, (sizeof(filePath)));

			// get file path as string
			std::wstring filePathAsWideString(filePath);
			std::string filePathAsString(filePathAsWideString.begin(), filePathAsWideString.end());

			// remove trailing file name
			size_t lastPathSeparatorPosition = filePathAsString.rfind(PathSeparator);
			std::string directoryPathAsString = filePathAsString.substr(0, lastPathSeparatorPosition);

			return directoryPathAsString;
		#endif

		#ifdef __ANDROID__
			throw Exception("This functionality is not supported on Android");
		#endif
	}

	bool EnvironmentHelper::IsMobile()
	{
		#if defined WIN32
			return false;
		#elif defined __ANDROID__
			return true;
		#else
			throw Exception("The current operating system is not supported");
		#endif
	}
}
