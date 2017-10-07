#pragma once

#include <string>

namespace Core 
{
	class AssetHelper
	{
	public:
		// load a text asset
		static std::string LoadTextAsset(std::string assetPath);
	};
}
 