#include "AssetHelper.h"

#include "../Libraries/SDL.h"
using namespace Libraries;

#include "../../Base/System/EnvironmentHelper.h"
#include "../../Base/System/Exception.h"
using namespace System;

#include <SDL2/SDL.h>

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
		Sint64 fileSize = SDL_RWsize(reader);
		char* data = (char*)malloc((size_t)fileSize + 1);
	
		Sint64 totalSize = 0; 
		Sint64 lastSize = 0;

		// read
		do
		{
			lastSize = SDL_RWread(reader, &data[totalSize], sizeof(char), (size_t)(fileSize - totalSize));
			totalSize += lastSize;	
		} while (totalSize < fileSize && lastSize != 0);
		data[totalSize] = '\0';

		// cleanup
		SDL_RWclose(reader);
		if (totalSize != fileSize)
		{
			throw Exception("Could not load text file: " + filePath);
		}

		return data;
	}
}