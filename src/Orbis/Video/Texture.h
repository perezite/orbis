#pragma once

#include "TextureAtlas.h"

#include "../Libraries/GL.h"
#include "../Libraries/SDL.h"

#include "../../Base/Math/Rect.h"
using namespace Math;

#include <string>
#include <set>

namespace Video
{
	class TextureAtlasPage;

	class Texture
	{
	public:
		// ctor
		Texture(std::string assetPath, bool flipVertically = true);

		// dtor
		virtual ~Texture();

		// get the texture handle
		unsigned int GetTextureHandle() const { return m_textureHandle; }

		// get the asset path
		std::string GetAssetPath() const { return m_assetPath; }

		// get the sdl surface
		SDL_Surface* GetSurface() { return m_surface; }

		// set the textures atlas page
		void SetTextureAtlasPage(TextureAtlasPage* page) { m_atlasPage = page; }

		// transform texture uv coordinates
		Vector2D MapUVCoord(Vector2D texUV);

		// bind this texture
		void Bind();

	private:
		// the texture asset path
		std::string m_assetPath;

		// the texture id
		GLuint m_textureHandle = 0;

		// the image surface
		SDL_Surface* m_surface;

		// the atlas page containing the texture
		TextureAtlasPage* m_atlasPage;

		// TODO: remove later
		bool m_hasAtlas;
	};
}