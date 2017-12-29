#pragma once

#include "Texture.h"

#include <vector>

namespace Video
{
	class TextureAtlas
	{
	public:
		// ctor
		TextureAtlas(std::vector<Texture*> textures);

		// add a range of textures
		void AddRange(std::vector<Texture*> textures);

	private:
		// the textures
		std::vector<Texture*> m_textures;
	};
}