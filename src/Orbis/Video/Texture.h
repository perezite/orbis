#pragma once

#include "../Libraries/GL.h"
#include "../Libraries/SDL.h"

#include <string>
#include <set>

namespace Video
{
	class Texture
	{
	public:
		// ctor
		Texture(std::string assetPath, bool flipVertically = true);

		// dtor
		virtual ~Texture();

		// get the texture handle
		unsigned int GetTextureHandle() const { return texture; }

		// get the asset path
		std::string GetAssetPath() const { return m_assetPath; }

		// bind this texture
		void Bind();

	private:
		// the texture asset path
		std::string m_assetPath;

		// the texture id
		GLuint texture;

		// the image surface
		SDL_Surface* m_surface;
	};
}