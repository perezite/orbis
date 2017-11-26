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
		unsigned int GetTextureHandle() { return m_textureHandle; }

		// bind this texture
		void Bind();

	private:
		// the texture id
		GLuint m_textureHandle;

		// the image surface
		SDL_Surface* m_surface;
	};
}