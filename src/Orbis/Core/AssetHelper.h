#pragma once

#include <string>

namespace Core 
{
	class AssetHelper
	{
	public:
		// convert an asset path to a file path
		static std::string assetPathToFilePath(std::string assetPath);

		// save a text asset. Overwrite any already existing data
		static void saveTextAsset(std::string assetPath, std::string text);

		// load a text asset
		static std::string loadTextAsset(std::string assetPath);

		// try load a text asset
		static bool tryLoadTextAsset(std::string assetPath, std::string& loadedText);
	};
}
 