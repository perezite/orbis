#pragma once

#include <string>

namespace core 
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

		// check if text asset exists
		static bool textAssetExists(std::string assetPath);

	};
}
 