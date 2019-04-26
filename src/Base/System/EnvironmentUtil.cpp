#include "EnvironmentUtil.h"

#include "Exception.h"
#include "StringUtil.h"

#ifdef WIN32
	#include <windows.h>
	#include <direct.h>
#endif
#include <string>

namespace base 
{ 
	const std::string EnvironmentUtil::PathSeparator = "\\";

	std::string EnvironmentUtil::getExecutableDirectoryPath()
	{
		#ifdef WIN32
			wchar_t filePath[MAX_PATH];

			// get executable file path
			HMODULE hModule = GetModuleHandle(NULL);
			Exception::assert(hModule != NULL, "GetModuleHandle() failed");
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

	bool EnvironmentUtil::isMobile()
	{
		#if defined WIN32
			return false;
		#elif defined __ANDROID__
			return true;
		#else
			throw Exception("The current operating system is not supported");
		#endif
	}

	std::string EnvironmentUtil::combinePath(std::vector<std::string> parts)
	{
		std::string result;
		for (unsigned int i = 0; i < parts.size() - 1; i++)
		{
			if (parts[i].size() > 0)
			{
				result += parts[i];
				result += PathSeparator;
			}
		}

		result += parts[parts.size() - 1];

		return result;
	}

	void EnvironmentUtil::writeToClipboard(std::string value)
	{
		#ifdef WIN32
			HWND windowHandle = GetDesktopWindow();
			OpenClipboard(windowHandle);
			EmptyClipboard();
			HGLOBAL valueHandle = GlobalAlloc(GMEM_MOVEABLE, value.size() + 1);
			if (!valueHandle) {
				CloseClipboard();
				throw Exception("GlobalAlloc() failed");
			}
			memcpy(GlobalLock(valueHandle), value.c_str(), value.size() + 1);
			GlobalUnlock(valueHandle);
			SetClipboardData(CF_TEXT, valueHandle);
			CloseClipboard();
			GlobalFree(valueHandle);
		#else
			throw Exception("The current operating system is not supported");
		#endif
	}
}