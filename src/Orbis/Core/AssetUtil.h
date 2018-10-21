#pragma once

#include <string>

namespace orb
{
	class AssetUtil
	{
	public:
		// convert an asset path to a file path
		static std::string assetPathToFilePath(std::string assetPath);

		// save a text asset. Overwrite any already existing data
		static void saveTextAsset(std::string assetPath, std::string text);

		// load a text asset
		static std::string loadTextAsset(std::string assetPath);

		// load a text asset line by line 
		static std::vector<std::string> loadTextAssetLines(std::string assetPath);

		// check if text asset exists
		static bool textAssetExists(std::string assetPath);

	};
}