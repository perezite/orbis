#pragma once

#include "Texture.h"

#include "../Libraries/SDL.h"
#include "../Libraries/GL.h"

#include "../../Base/Base.h"
using namespace base;

#include <vector>
#include <map>

namespace orb
{
	class Texture;

	class TextureChart
	{
	public:
		// ctor
		TextureChart(std::vector<Texture*> textures, std::vector<Rect> rects);

		// dtor
		virtual ~TextureChart();

		// get the uv rect of the texture within the page
		Rect getUVRect(Texture* tex) {
			return m_uvRects.find(tex)->second;
		}

		// bind the page texture
		void bind();

	protected:
		// convert a Rect to an SDL_Rect
		SDL_Rect toSDLRect(Rect rect);

		// get smallest power of two size still containing all texture rects
		Vector2f getSmallestPowerOfTwoSize(std::vector<Rect> rects);

		// get a tight boundary around all texture rects within the page
		Rect getBoundaryRect(std::vector<Rect> rects);

		// get next larger power of two for a given integer
		int getNextPowerOfTwo(int number);

		// copy sdl surfaces from textures to atlas surface
		void copySurfaces(std::vector<Texture*> textures, std::vector<Rect> rects, SDL_Surface* pageSurface);

		// create the opengl texture
		void createPageTexture(SDL_Surface* surface);

		// get the rect of an sdl surface
		SDL_Rect getSurfaceRect(SDL_Surface* surface);

		// store uv rects in textures
		void storeUVRects(std::vector<Texture*> textures, std::vector<Rect> rects, SDL_Surface* surface);

		// register the page at the contained textures
		void registerTextures(std::vector<Texture*> textures);

	private:
		// the gl texture handle
		GLuint m_textureHandle;

		// the textures uv rects
		std::map<Texture*, Rect> m_uvRects;
	};
}