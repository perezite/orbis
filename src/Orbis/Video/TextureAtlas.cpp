#include "TextureAtlas.h"

#include "../../Base/System/Exception.h"
#include "../../Base/Algorithms/BinPacking.h"
using namespace System;
using namespace Algorithms;

namespace Video
{
	TextureAtlas* TextureAtlas::GetInstance()
	{
		static TextureAtlas instance;
		return &instance;
	}

	void TextureAtlas::Add(Texture* texture)
	{
		m_textures.push_back(texture);
	}

	void TextureAtlas::Generate()
	{
		// compute the bin / page rect
		GLint pageSize;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &pageSize);
		Rect bin = Rect(0, 0, (float)pageSize, (float)pageSize);

		// pack the texture Rects
		std::vector<std::vector<Rect>> pageRectsCollection = BinPacking::Execute(bin, GetTextureRects());

		// create pages
		for (unsigned int i = 0; i < pageRectsCollection.size(); i++)
		{
			std::vector<Rect> pageRects = pageRectsCollection[i];
			std::vector<Texture*> pageTextures = SelectTextures(pageRects);
			TextureChart* page = new TextureChart(pageTextures, pageRects);
			m_charts.push_back(page);
		}
	}

	TextureAtlas::~TextureAtlas()
	{
		for (unsigned int i = 0; i < m_charts.size(); i++)
			delete m_charts[i];
	}

	std::vector<Rect> TextureAtlas::GetTextureRects()
	{
		std::vector<Rect> textureRects;

		for (unsigned int i = 0; i < m_textures.size(); i++)
		{
			Rect rect = ToOrbisRect(GetSurfaceRect(m_textures[i]->GetSurface()));
			rect.index = i;
			textureRects.push_back(rect);
		}

		return textureRects;
	}

	std::vector<Texture*> TextureAtlas::SelectTextures(std::vector<Rect> indexedRects)
	{
		std::vector<Texture*> textures;

		for (unsigned int i = 0; i < indexedRects.size(); i++)
		{
			unsigned int texIndex = indexedRects[i].index;
			textures.push_back(m_textures[texIndex]);
		}

		return textures;
	}

	SDL_Rect TextureAtlas::GetSurfaceRect(SDL_Surface* surface)
	{
		SDL_Rect rect;
		rect.x = 0; rect.y = 0; rect.h = surface->h; rect.w = surface->w;
		return rect;
	}

	Rect TextureAtlas::ToOrbisRect(SDL_Rect rect)
	{
		return Rect((float)rect.x, (float)rect.y, (float)rect.x + (float)rect.w, (float)rect.y + (float)rect.h);
	}
}
