#include "AssetHelper.h"

#include "../Libraries/SDL.h"
using namespace Libraries;

#include "../../Base/System/EnvironmentHelper.h"
#include "../../Base/System/Exception.h"
using namespace System;

namespace
{
	std::string GetAssetFolderPath()
	{
		#ifdef WIN32
			return EnvironmentHelper::CombinePath({ EnvironmentHelper::GetExecutableDirectoryPath(), "..", "Assets" });
		#endif
		
		#ifdef __ANDROID__
			return "";
		#endif
	}

	std::string AssetPathToFilePath(std::string assetPath)
	{
		return EnvironmentHelper::CombinePath({ GetAssetFolderPath(), assetPath });
	}
}

namespace Core
{
	std::string AssetHelper::LoadTextAsset(std::string assetPath)
	{
		std::string filePath = AssetPathToFilePath(assetPath);

		// setup
		SDL::File* reader = SDL::OpenFile(filePath.c_str(), "r");
		SDL::SignedLong fileSize = SDL::GetFileSize(reader);
		char* data = (char*)malloc((size_t)fileSize + 1);
	
		SDL::SignedLong totalSize = 0; 
		SDL::SignedLong lastSize = 0;

		// read
		do
		{
			lastSize = SDL::ReadFromFile(reader, &data[totalSize], sizeof(char), (size_t)(fileSize - totalSize));
			totalSize += lastSize;	
		} while (totalSize < fileSize && lastSize != 0);
		data[totalSize] = '\0';

		// cleanup
		SDL::CloseFile(reader);

		return data;
	}
}