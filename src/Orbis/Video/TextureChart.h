#pragma once

#include "Texture.h"

#include "../Libraries/SDL.h"
#include "../Libraries/GL.h"

#include "../../Base/Math/Rect.h"
using namespace Math;

#include <vector>
#include <map>

namespace Video
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
		Rect GetUVRect(Texture* tex) { 
			return m_uvRects.find(tex)->second; 
		}

		// bind the page texture
		void Bind();

	protected:
		// convert a Rect to an SDL_Rect
		SDL_Rect ToSDLRect(Rect rect);

		// get smallest power of two size still containing all texture rects
		Vector2D GetSmallestPowerOfTwoSize(std::vector<Rect> rects);

		// get a tight boundary around all texture rects within the page
		Rect GetBoundaryRect(std::vector<Rect> rects);

		// get next larger power of two for a given integer
		int GetNextPowerOfTwo(int number);

		// copy sdl surfaces from textures to atlas surface
		void CopySurfaces(std::vector<Texture*> textures, std::vector<Rect> rects, SDL_Surface* pageSurface);

		// create the opengl texture
		void CreatePageTexture(SDL_Surface* surface);

		// get the rect of an sdl surface
		SDL_Rect GetSurfaceRect(SDL_Surface* surface);

		// store uv rects in textures
		void StoreUVRects(std::vector<Texture*> textures, std::vector<Rect> rects, SDL_Surface* surface);

		// register the page at the contained textures
		void RegisterTextures(std::vector<Texture*> textures);

	private:
		// the gl texture handle
		GLuint m_textureHandle;

		// the textures uv rects
		std::map<Texture*, Rect> m_uvRects;
	};
}