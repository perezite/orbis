#pragma once

#include "TextureAtlas.h"

#include "../Libraries/GL.h"
#include "../Libraries/SDL.h"
#include "../Game/Level.h"
using namespace Game;

#include "../../Base/Math/Rect.h"
using namespace Math;

#include <string>
#include <set>

namespace Game
{
	class Level;
}

namespace Video
{
	class TextureChart;

	class Texture
	{
	public:
		// ctor
		Texture(Level* parentLevel, std::string assetPath, bool flipVertically = true);

		// dtor
		virtual ~Texture();

		// get the texture handle
		unsigned int GetTextureHandle() const { return m_handle; }

		// get the asset path
		std::string GetAssetPath() const { return m_assetPath; }

		// get the sdl surface
		SDL_Surface* GetSurface() { return m_surface; }

		// get the gl handle
		GLuint GetHandle() { return m_handle; }

		// set the textures atlas page
		void SetTextureAtlasPage(TextureChart* page) { m_atlasChart = page; }

		// transform texture uv coordinates
		Vector2D MapUVCoord(Vector2D texUV);

		// bind this texture
		void Bind();

		// is the texture using atlassing
		bool UsesAtlassing() const;
		
		// get the atlas texture chart
		TextureChart* GetAtlasChart() const { return m_atlasChart; }

	private:
		// the texture asset path
		std::string m_assetPath;

		// the texture id
		GLuint m_handle = 0;
		
		// the image surface
		SDL_Surface* m_surface;

		// the texture chart containing the texture
		TextureChart* m_atlasChart;
	};
}