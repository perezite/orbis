#include "EnvironmentHelper.h"

#include "Exception.h"
#include "StringHelper.h"


#ifdef _WIN32
	#include <windows.h>
	#include <direct.h>
#endif

#include <string>

namespace System
{
	const std::string Win32PathSeparator = "\\";

	std::string EnvironmentHelper::GetWorkingDirectory()
	{
		#ifdef _WIN32
			wchar_t workingDirectory[MAX_PATH];
			int bytes = GetCurrentDirectory(MAX_PATH, workingDirectory);
			std::wstring directoryPathAsWideString = std::wstring(workingDirectory);
			std::string directoryPathAsString(directoryPathAsWideString.begin(), directoryPathAsWideString.end());
			return directoryPathAsString;
		#endif	
	}

	std::string System::EnvironmentHelper::GetExecutableDirectoryPath()
	{
		#ifdef _WIN32
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
			size_t lastPathSeparatorPosition = filePathAsString.rfind(GetPathSeparator());
			std::string directoryPathAsString = filePathAsString.substr(0, lastPathSeparatorPosition);

			return directoryPathAsString;
		#endif
	}


	void EnvironmentHelper::SetWorkingDirectory(std::string workingDirectoryPath)
	{
		#ifdef _WIN32
			int result = _chdir(workingDirectoryPath.c_str());
			if (result != 0)
				throw new Exception("_chdir() failed");
		#endif
	}

	std::string EnvironmentHelper::GetPathSeparator()
	{
		#ifdef _WIN32 
			return Win32PathSeparator;
		#endif	
	}
}
