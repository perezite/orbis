#pragma once

#include "Atlas.h"

#include "../Libraries/GL.h"
#include "../Libraries/SDL.h"
#include "../Game/Level.h"

#include "../../Base/Base.h"
using namespace base;

#include <string>
#include <set>

namespace orb
{
	class Level;

	class Sheet;

	class Texture
	{
	public:
		// ctor
		Texture(const std::string& assetPath, bool flipVertically = true);

		// dtor
		virtual ~Texture();

		// get the asset path
		const std::string& getAssetPath() const { return m_assetPath; }

		// get the sdl surface
		SDL_Surface* getSurface() { return m_surface; }

		// get the gl handle
		GLuint getHandle() { return m_handle; }

		// is the texture on a sheet
		bool isOnSheet() const { return m_parentSheet != NULL; }

		// get the sheet
		const Sheet* getParentSheet() const { return m_parentSheet; }

		// transfer ownership of the texture to the given sheet - private texture data gets released.
		void transferOwnershipToSheet(Sheet* parentSheet);

		// get the rect encompassing the texture in local coordinates
		const Rect getLocalRect() const;

		// transform given local texture coordinates to coordinates within the parent sheet
		Vector2f localToSheetPosition(const Vector2f& texPosition);

		// bind the texture
		void bind();

	protected:
		// convert surface to given pixel format. The surface pointer is invalidated and gets replaced by the returned pointer
		SDL_Surface* convertPixelFormat(SDL_Surface* surface, Uint32 pixelFormat);

		// flip the gisven surface. The surface pointer is invalidated and gets replaced by the returned pointer 
		SDL_Surface* flipSurfaceVertically(SDL_Surface* surface);

	private:
		// the texture asset path
		std::string m_assetPath;

		// the open gl texture handle
		GLuint m_handle;

		// the sdl surface
		SDL_Surface* m_surface;

		// the parent sheet containing the texture
		Sheet* m_parentSheet;
	};
}