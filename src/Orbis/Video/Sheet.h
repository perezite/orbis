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

	// a sheet is a big texture which contains several other textures. Can be used to speed up rendering
	class Sheet
	{
	public:
		// ctor
		Sheet(const std::vector<Texture*>& textures, const std::vector<Rect>& rects);

		// dtor
		virtual ~Sheet();

		// get the uv rect of the texture within the sheet
		const Rect& getUVRect(Texture* tex) const;

		// bind the sheet
		void bind();

	protected:
		// create a surface with the smallest possible power of two size still holding all the given textures with their rects
		SDL_Surface* createSheetSurface(const std::vector<Texture*>& textures, const std::vector<Rect>& rects);

		// transfer the surfaces with their rects to the given surface
		void copyTextureDataToSurface(const std::vector<Texture*>& textures, const std::vector<Rect>& rects, SDL_Surface* surface);

		// store uv rects in textures
		const std::map<Texture*, Rect> computeUVRects(const std::vector<Texture*>& textures, const std::vector<Rect>& rects, SDL_Surface* surface);

		// transfer the data from the surface to an opengl texture and free the surface
		void copySheetSurfaceToOpenGl(SDL_Surface* surface);

		// register the page at the contained textures
		void registerTextures(const std::vector<Texture*>& textures);

		// get next larger power of two rect
		const Rect getNextLargerPowerOfTwoRect(const Rect& rect);

		// convert a rect to an SDL_Rect
		const SDL_Rect toSdlRect(const Rect& rect);

		// get the rect of an sdl surface
		const SDL_Rect getSurfaceRect(const SDL_Surface* surface);

		// compute a tight boundary around the given rects
		const Rect computeBoundaryRect(const std::vector<Rect>& rects);

	private:
		// the gl texture handle
		GLuint m_textureHandle;

		// the textures uv rects
		std::map<Texture*, Rect> m_uvRects;
	};
}