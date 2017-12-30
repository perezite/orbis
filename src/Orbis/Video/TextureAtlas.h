#pragma once

#include "Texture.h"

#include <vector>

namespace Video
{
	class TextureAtlasPage
	{
	public:
		// ctor
		TextureAtlasPage();

	private:
		// maximum size
		int m_maxSize;
	};

	class TextureAtlas
	{
	public:
		// get singleton instance
		static TextureAtlas* GetInstance();

		// add a texture 
		void Add(Texture* texture);

		// generate the atlas
		void Generate();

	private:
		// the textures
		std::vector<TextureAtlasPage> m_pages;
	};
}