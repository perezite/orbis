#pragma once

#include <string>

namespace Core 
{
	class AssetHelper
	{
	public:
		// convert an asset path to a file path
		static std::string AssetPathToFilePath(std::string assetPath);

		// save a text asset. Overwrite any already existing data
		static void SaveTextAsset(std::string assetPath, std::string text);

		// load a text asset
		static std::string LoadTextAsset(std::string assetPath);

		// try load a text asset
		static bool TryLoadTextAsset(std::string assetPath, std::string& loadedText);
	};
}
 