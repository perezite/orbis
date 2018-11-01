#include "TextureAtlas.h"

#include "VideoManager.h"

#include "../../Base/Base.h"
using namespace base;

namespace orb
{
	void TextureAtlas::clear()
	{
		MemoryUtil::clear(m_charts);
		m_textures.clear();
	}

	void TextureAtlas::generate()
	{
		// compute chart extent
		GLint chartExtent;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &chartExtent);

		// pack
		std::vector<Texture*> textures = VideoManager::instance()->getTextures();
		AtlasPacking atlasPacking = packAtlas(textures, (float)chartExtent, (float)chartExtent);

		// create charts
		createCharts(atlasPacking);
	}

	AtlasPacking TextureAtlas::packAtlas(std::vector<Texture*> textures, float width, float height)
	{
		AtlasPacking atlasPacking;
		std::vector<Rect> indexedRects = getIndexedTextureRects(textures);
		std::vector<std::vector<Rect>> packedRects = BinPacking::calculate(Rect(0, 0, width, height), indexedRects);

		for (unsigned int i = 0; i < packedRects.size(); i++) {
			atlasPacking.push_back(packChart(packedRects[i], textures));
		}

		return atlasPacking;
	}

	std::vector<Rect> TextureAtlas::getIndexedTextureRects(const std::vector<Texture*>& textures)
	{
		std::vector<Rect> textureRects;
		for (unsigned int i = 0; i < textures.size(); i++) {
			Rect localTextureRect = textures[i]->getLocalRect();
			localTextureRect.index = i;
			textureRects.push_back(localTextureRect);
		}

		return textureRects;
	}

	ChartPacking TextureAtlas::packChart(const std::vector<Rect>& rects, const std::vector<Texture*>& textures)
	{
		ChartPacking chartPacking;
		for (unsigned int i = 0; i < rects.size(); i++) {
			Rect rect = rects[i];
			Texture* tex = textures[rect.index];
			std::tuple<Texture*, Rect> packedTexture(std::make_tuple(tex, rect));
			chartPacking.push_back(packedTexture);
		}

		return chartPacking;
	}

	void TextureAtlas::createCharts(const AtlasPacking& atlasPacking)
	{
		for (unsigned int i = 0; i < atlasPacking.size(); i++) {
			ChartPacking chartPacking = atlasPacking[i];
			std::vector<Texture*> textures = getTextures(chartPacking);
			std::vector<Rect> rects = getRects(chartPacking);
			m_charts.push_back(new TextureChart(textures, rects));
		}
	}

	std::vector<Texture*> TextureAtlas::getTextures(const ChartPacking& packing)
	{
		std::vector<Texture*> textures;
		for (unsigned int i = 0; i < packing.size(); i++) 
			textures.push_back(std::get<0>(packing[i]));
		return textures;
	}

	std::vector<Rect> TextureAtlas::getRects(const ChartPacking& packing)
	{
		std::vector<Rect> rects;
		for (unsigned int i = 0; i < packing.size(); i++)
			rects.push_back(std::get<1>(packing[i]));
		return rects;
	}
}