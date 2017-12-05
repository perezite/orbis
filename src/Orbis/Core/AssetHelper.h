#pragma once

#include <string>

namespace Core 
{
	class AssetHelper
	{
	public:
		// convert an asset path to a file path
		static std::string AssetPathToFilePath(std::string assetPath);

		// load a text asset
		static std::string LoadTextAsset(std::string assetPath);
	};
}
 