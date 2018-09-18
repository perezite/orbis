#pragma once

#include "TextureAtlas.h"

#include "../Libraries/GL.h"
#include "../Libraries/SDL.h"
#include "../Game/Level.h"
using namespace orb::game;

#include "../../Base/Math/Rect.h"
using namespace base;

#include <string>
#include <set>

namespace orb
{
	namespace game
	{
		class Level;
	}

	namespace video
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
			unsigned int getTextureHandle() const { return m_handle; }

			// get the asset path
			std::string getAssetPath() const { return m_assetPath; }

			// get the sdl surface
			SDL_Surface* getSurface() { return m_surface; }

			// get the gl handle
			GLuint getHandle() { return m_handle; }

			// set the textures atlas page
			void setTextureAtlasPage(TextureChart* page) { m_atlasChart = page; }

			// transform texture uv coordinates
			Vector2D mapUVCoord(Vector2D texUV);

			// bind this texture
			void bind();

			// is the texture using atlassing
			bool isUsingAtlassing() const;

			// get the atlas texture chart
			TextureChart* getAtlasChart() const { return m_atlasChart; }

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
}