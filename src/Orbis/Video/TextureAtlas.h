#pragma once

#include "TextureChart.h"

#include "../Libraries/SDL.h"
#include "../Libraries/GL.h"

#include "../../Base/Math/Rect.h"
using namespace base;

#include <vector>
#include <map>

namespace orb
{
	namespace video
	{
		class Texture;

		class TextureChart;

		class TextureAtlas
		{
		public:
			// dtor
			virtual ~TextureAtlas() { };

			// add a texture 
			void add(Texture* texture);

			// clear the atlas
			void clear();

			// generate the atlas
			void generate();

		protected:
			// get texture rects
			std::vector<Rect> getTextureRects();

			// select textures by indexed rects
			std::vector<Texture*> selectTextures(std::vector<Rect> indexedRects);

			// get the rect of an sdl surface
			SDL_Rect getSurfaceRect(SDL_Surface* surface);

			// convert sdl rect to orbis rect
			Rect toOrbisRect(SDL_Rect rect);

		private:
			// the textures
			std::vector<Texture*> m_textures;

			// the pages
			std::vector<TextureChart*> m_charts;
		};
	}
}