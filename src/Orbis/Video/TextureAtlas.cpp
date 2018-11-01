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
		// get the extent of one chart
		GLint chartExtent;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &chartExtent);

		// generate the individual charts
		std::vector<Texture*> textures = VideoManager::instance()->getTextures();
		AtlasPacking atlasPacking = packTextures(textures, (float)chartExtent, (float)chartExtent);
		createCharts(atlasPacking);
	}

	AtlasPacking TextureAtlas::packTextures(std::vector<Texture*> textures, float width, float height)
	{
		AtlasPacking atlasPacking;
		std::vector<Rect> indexedRects = getIndexedTextureRects(textures);
		std::vector<std::vector<Rect>> packedRects = BinPacking::calculate(Rect(0, 0, width, height), indexedRects);

		for (unsigned int i = 0; i < packedRects.size(); i++) {
			ChartPacking chartPacking;
			for (unsigned int j = 0; j < packedRects[i].size(); j++) {
				Rect rect = packedRects[i][j];
				Texture* tex = textures[rect.index];
				std::tuple<Texture*, Rect> packedTexture(std::make_tuple(tex, rect));
				chartPacking.push_back(packedTexture);
			}

			atlasPacking.push_back(chartPacking);
		}

		return atlasPacking;
	}

	std::vector<Rect> TextureAtlas::getIndexedTextureRects(std::vector<Texture*> textures)
	{
		std::vector<Rect> textureRects;
		for (unsigned int i = 0; i < textures.size(); i++) {
			Rect localTextureRect = textures[i]->getLocalRect();
			localTextureRect.index = i;
			textureRects.push_back(localTextureRect);
		}

		return textureRects;
	}

	void TextureAtlas::createCharts(AtlasPacking atlasPacking)
	{
		for (unsigned int i = 0; i < atlasPacking.size(); i++) {
			ChartPacking chartPacking = atlasPacking[i];
			std::vector<Texture*> textures = getTextures(chartPacking);
			std::vector<Rect> rects = getRects(chartPacking);
			m_charts.push_back(new TextureChart(textures, rects));
		}
	}

	std::vector<Texture*> TextureAtlas::getTextures(ChartPacking packing)
	{
		std::vector<Texture*> textures;
		for (unsigned int i = 0; i < packing.size(); i++) 
			textures.push_back(std::get<0>(packing[i]));
		return textures;
	}

	std::vector<Rect> TextureAtlas::getRects(ChartPacking packing)
	{
		std::vector<Rect> rects;
		for (unsigned int i = 0; i < packing.size(); i++)
			rects.push_back(std::get<1>(packing[i]));
		return rects;
	}
}