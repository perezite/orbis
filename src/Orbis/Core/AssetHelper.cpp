#include "AssetHelper.h"

#include "../Libraries/SDL.h"

#include "../../Base/System/EnvironmentHelper.h"
#include "../../Base/System/Exception.h"
using namespace base::system;

namespace
{
	std::string GetAssetFolderPath()
	{
		#ifdef WIN32
			return EnvironmentHelper::combinePath({ EnvironmentHelper::getExecutableDirectoryPath(), "..", "Assets" });
		#endif
		
		#ifdef __ANDROID__
			return "";
		#endif
	}
}

namespace orb
{
	namespace core
	{
		std::string AssetHelper::assetPathToFilePath(std::string assetPath)
		{
			return EnvironmentHelper::combinePath({ GetAssetFolderPath(), assetPath });
		}

		void AssetHelper::saveTextAsset(std::string assetPath, std::string text)
		{
			std::string filePath = assetPathToFilePath(assetPath);

			SDL_RWops *writer = SDL_RWFromFile_Checked(filePath.c_str(), "w");
			size_t len = SDL_strlen(text.c_str());

			SDL_RWwrite(writer, text.c_str(), 1, len);
			SDL_RWclose(writer);
		}

		std::string AssetHelper::loadTextAsset(std::string assetPath)
		{
			std::string filePath = assetPathToFilePath(assetPath);

			// setup
			SDL_RWops* reader = SDL_RWFromFile_Checked(filePath.c_str(), "r");
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
			SDL_RWclose(reader);

			// check
			Exception::assert(totalSize == fileSize, "Could not load file '" + assetPath + "'");

			return data;
		}

		bool AssetHelper::textAssetExists(std::string assetPath)
		{
			std::string filePath = assetPathToFilePath(assetPath);
			SDL_RWops* reader = SDL_RWFromFile(filePath.c_str(), "r");
			bool exists = reader != NULL;

			SDL_RWclose(reader);
			return exists;
		}
	}
}