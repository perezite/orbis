#include "Atlas.h"

#include "VideoManager.h"

#include "../../Base/Base.h"
using namespace base;

namespace orb
{
	void Atlas::clear()
	{
		MemoryUtil::clear(m_sheets);
		m_textures.clear();
	}

	void Atlas::generate()
	{
		GLint sheetExtent;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &sheetExtent);

		std::vector<Texture*> textures = VideoManager::instance()->getTextures();
		AtlasPacking atlasPacking = packAtlas(textures, (float)sheetExtent, (float)sheetExtent);

		createSheets(atlasPacking);
	}

	AtlasPacking Atlas::packAtlas(std::vector<Texture*> textures, float width, float height)
	{
		AtlasPacking atlasPacking;
		std::vector<Rect> indexedRects = getIndexedTextureRects(textures);
		std::vector<std::vector<Rect>> packedRects = BinPacking::calculate(Rect(0, 0, width, height), indexedRects);

		for (unsigned int i = 0; i < packedRects.size(); i++) {
			atlasPacking.push_back(packSheet(packedRects[i], textures));
		}

		return atlasPacking;
	}

	std::vector<Rect> Atlas::getIndexedTextureRects(const std::vector<Texture*>& textures)
	{
		std::vector<Rect> textureRects;
		for (unsigned int i = 0; i < textures.size(); i++) {
			Rect localTextureRect = textures[i]->getLocalRect();
			localTextureRect.index = i;
			textureRects.push_back(localTextureRect);
		}

		return textureRects;
	}

	SheetPacking Atlas::packSheet(const std::vector<Rect>& rects, const std::vector<Texture*>& textures)
	{
		SheetPacking sheetPacking;
		for (unsigned int i = 0; i < rects.size(); i++) {
			Rect rect = rects[i];
			Texture* tex = textures[rect.index];
			std::tuple<Texture*, Rect> packedTexture(std::make_tuple(tex, rect));
			sheetPacking.push_back(packedTexture);
		}

		return sheetPacking;
	}

	void Atlas::createSheets(const AtlasPacking& atlasPacking)
	{
		for (unsigned int i = 0; i < atlasPacking.size(); i++) {
			SheetPacking sheetPacking = atlasPacking[i];
			std::vector<Texture*> textures = getTextures(sheetPacking);
			std::vector<Rect> rects = getRects(sheetPacking);
			m_sheets.push_back(new Sheet(textures, rects));
		}
	}

	std::vector<Texture*> Atlas::getTextures(const SheetPacking& packing)
	{
		std::vector<Texture*> textures;
		for (unsigned int i = 0; i < packing.size(); i++) 
			textures.push_back(std::get<0>(packing[i]));
		return textures;
	}

	std::vector<Rect> Atlas::getRects(const SheetPacking& packing)
	{
		std::vector<Rect> rects;
		for (unsigned int i = 0; i < packing.size(); i++)
			rects.push_back(std::get<1>(packing[i]));
		return rects;
	}
}