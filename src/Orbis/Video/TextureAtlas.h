#pragma once

#include "TextureChart.h"

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
	class TextureChart;

	typedef std::vector<std::tuple<Texture*, Rect>> ChartPacking;
	typedef std::vector<ChartPacking> AtlasPacking;

	class TextureAtlas
	{
	public:
		// ctor
		TextureAtlas()
		{ }

		// dtor
		virtual ~TextureAtlas() { };

		// clear the atlas
		void clear();

		// generate the atlas
		void generate();

	protected:
		// pack the given textures into one ore more rectangles with the specified width and heigth
		AtlasPacking packTextures(std::vector<Texture*> textures, float width, float height);

		// get indexed texture rects
		std::vector<Rect> getIndexedTextureRects(std::vector<Texture*> textures);

		// create individual charts from an atlas packing
		void createCharts(AtlasPacking atlasPacking);

		// extract the textures from a packing
		std::vector<Texture*> getTextures(ChartPacking packing);

		// extract the rects from a packing
		std::vector<Rect> getRects(ChartPacking packing);

	private:
		// the textures
		std::vector<Texture*> m_textures;

		// the pages
		std::vector<TextureChart*> m_charts;
	};
}