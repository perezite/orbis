#include "TextureAtlas.h"

#include "../../Base/System/Exception.h"
#include "../../Base/System/MemoryHelper.h"
#include "../../Base/Algorithms/BinPacking.h"
using namespace System;
using namespace Algorithms;

namespace Video
{
	void TextureAtlas::add(Texture* texture)
	{
		m_textures.push_back(texture);
	}

	void TextureAtlas::clear()
	{
		MemoryHelper::clear(m_charts);
		m_textures.clear();
	}

	void TextureAtlas::generate()
	{
		// compute the bin / page rect
		GLint pageSize;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &pageSize);
		Rect bin = Rect(0, 0, (float)pageSize, (float)pageSize);

		// pack the texture Rects
		std::vector<std::vector<Rect>> pageRectsCollection = BinPacking::Execute(bin, getTextureRects());

		// create charts
		for (unsigned int i = 0; i < pageRectsCollection.size(); i++)
		{
			std::vector<Rect> pageRects = pageRectsCollection[i];
			std::vector<Texture*> pageTextures = selectTextures(pageRects);
			TextureChart* page = new TextureChart(pageTextures, pageRects);
			m_charts.push_back(page);
		}
	}

	std::vector<Rect> TextureAtlas::getTextureRects()
	{
		std::vector<Rect> textureRects;

		for (unsigned int i = 0; i < m_textures.size(); i++)
		{
			Rect rect = toOrbisRect(getSurfaceRect(m_textures[i]->getSurface()));
			rect.index = i;
			textureRects.push_back(rect);
		}

		return textureRects;
	}

	std::vector<Texture*> TextureAtlas::selectTextures(std::vector<Rect> indexedRects)
	{
		std::vector<Texture*> textures;

		for (unsigned int i = 0; i < indexedRects.size(); i++)
		{
			unsigned int texIndex = indexedRects[i].index;
			textures.push_back(m_textures[texIndex]);
		}

		return textures;
	}

	SDL_Rect TextureAtlas::getSurfaceRect(SDL_Surface* surface)
	{
		SDL_Rect rect;
		rect.x = 0; rect.y = 0; rect.h = surface->h; rect.w = surface->w;
		return rect;
	}

	Rect TextureAtlas::toOrbisRect(SDL_Rect rect)
	{
		return Rect((float)rect.x, (float)rect.y, (float)rect.x + (float)rect.w, (float)rect.y + (float)rect.h);
	}
}
