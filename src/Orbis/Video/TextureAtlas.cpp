#include "TextureAtlas.h"

#include "VideoManager.h"

#include "../../Base/Base.h"
using namespace base;

namespace orb
{
	void TextureAtlas::add(Texture* texture)
	{
		m_textures.push_back(texture);
	}

	void TextureAtlas::add(std::vector<std::string> textures)
	{
		for (unsigned int i = 0; i < textures.size(); i++)
		{
			VideoManager::instance().getTexture(textures[i]);
		}
	}

	void TextureAtlas::clear()
	{
		MemoryUtil::clear(m_charts);
		m_textures.clear();
		m_isGenerated = false;
	}

	void TextureAtlas::generate()
	{
		// compute the bin / page rect
		GLint pageSize;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &pageSize);
		Rect bin = Rect(0, 0, (float)pageSize, (float)pageSize);

		// pack the texture Rects
		std::vector<std::vector<Rect>> pageRectsCollection = BinPacking::calculate(bin, getTextureRects());

		// create charts
		for (unsigned int i = 0; i < pageRectsCollection.size(); i++)
		{
			std::vector<Rect> pageRects = pageRectsCollection[i];
			std::vector<Texture*> pageTextures = selectTextures(pageRects);
			TextureChart* page = new TextureChart(pageTextures, pageRects);
			m_charts.push_back(page);
		}

		m_isGenerated = true;
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