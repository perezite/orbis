#pragma once

#include "Component.h"

#include <string>

namespace Components
{
	// A renderer which renders a textured quad
	class TextureRenderer : public Component
	{
	public:
		// start
		void Start();

	protected: 
		// get the asset path from the filename
		std::string GetFilePathFromAssetPath(std::string assetPath);

	private:
		// the path of the texture asset
		std::string m_filePath;
	};
}