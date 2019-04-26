#pragma once

#include "Sheet.h"

#include "../Libraries/SDL.h"
#include "../Libraries/GL.h"

#include "../../Base/Base.h"
using namespace base;

#include <vector>
#include <map>
#include <tuple>

namespace orb
{
	class Texture;
	class Sheet;

	typedef std::vector<std::tuple<Texture*, Rect>> SheetPacking;
	typedef std::vector<SheetPacking> AtlasPacking;

	// An atlas is a collection of sheets. Maybe, this should be called TexturePacker instead...
	class Atlas
	{
	public:
		// ctor
		Atlas()
		{ }

		// dtor
		virtual ~Atlas() { };

		// clear the atlas
		void clear();

		// generate the atlas
		void generate();

	protected:
		// pack the given textures into one ore more rectangles with the specified width and heigth
		AtlasPacking packAtlas(std::vector<Texture*> textures, float width, float height);

		// get indexed texture rects
		std::vector<Rect> getIndexedTextureRects(const std::vector<Texture*>& textures);

		// pack the given textures into a sheet
		SheetPacking packSheet(const std::vector<Rect>& rects, const std::vector<Texture*>& textures);

		// create individual sheet from an atlas packing
		void createSheets(const AtlasPacking& atlasPacking);

		// extract the textures from a packing
		std::vector<Texture*> getTextures(const SheetPacking& packing);

		// extract the rects from a packing
		std::vector<Rect> getRects(const SheetPacking& packing);

	private:
		// the textures
		std::vector<Texture*> m_textures;

		// the pages
		std::vector<Sheet*> m_sheets;
	};
}