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
	class TextureChart;

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
		void SetTextureAtlasPage(TextureChart* page) { m_atlasChart = page; }

		// transform texture uv coordinates
		Vector2D MapUVCoord(Vector2D texUV);

		// bind this texture
		void Bind();

		// is the texture using atlassing
		bool UseAtlassing() const { return m_useAtlassing; }
		
		// get the atlas texture chart
		TextureChart* GetAtlasChart() const { return m_atlasChart; }

	private:
		// the texture asset path
		std::string m_assetPath;

		// the texture id
		GLuint m_textureHandle = 0;

		// the image surface
		SDL_Surface* m_surface;

		// the texture chart containing the texture
		TextureChart* m_atlasChart;

		// is the texture using texture atlassing
		bool m_useAtlassing;
	};
}