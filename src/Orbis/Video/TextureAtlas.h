#pragma once

#include "TextureChart.h"

#include "../Libraries/SDL.h"
#include "../Libraries/GL.h"

#include "../../Base/Math/Rect.h"
using namespace Math;

#include <vector>
#include <map>

namespace Video
{
	class Texture;

	class TextureChart;

	class TextureAtlas
	{
	public:
		// dtor
		virtual ~TextureAtlas() { };

		// add a texture 
		void Add(Texture* texture);

		// clear the atlas
		void Clear();

		// generate the atlas
		void Generate();

	protected:
		// get texture rects
		std::vector<Rect> GetTextureRects();

		// select textures by indexed rects
		std::vector<Texture*> SelectTextures(std::vector<Rect> indexedRects);

		// get the rect of an sdl surface
		SDL_Rect GetSurfaceRect(SDL_Surface* surface);

		// convert sdl rect to orbis rect
		Rect ToOrbisRect(SDL_Rect rect);

	private:
		// the textures
		std::vector<Texture*> m_textures;

		// the pages
		std::vector<TextureChart*> m_charts;
	};
}