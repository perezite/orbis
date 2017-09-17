#include "TextureRenderer.h"

#include "../../Base/System/EnvironmentHelper.h"
using namespace System;

#include <vector>

namespace Components
{
	void TextureRenderer::Start() 
	{ 
		std::string m_filePath = 
			EnvironmentHelper::CombinePath({ EnvironmentHelper::GetExecutableDirectoryPath(), "..", "Assets", "TestTransparent.png" });
	}

	std::string TextureRenderer::GetFilePathFromAssetPath(std::string assetPath)
	{
		return "";
	}
}