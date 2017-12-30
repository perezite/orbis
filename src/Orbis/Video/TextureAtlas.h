#pragma once

#include "Texture.h"

#include <vector>

namespace Video
{
	class TextureAtlas
	{
	public:
		// get singleton instance
		TextureAtlas* GetInstance();

		// add a range of textures
		void AddRange(std::vector<Texture*> textures);

	protected:
		// singleton ctor
		TextureAtlas() {};

	private:
		// the textures
		std::vector<Texture*> m_textures;

		// maximum page atlas width/height
		static const unsigned int MAX_ATLAS_SIZE;
	};
}