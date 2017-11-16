#pragma once

#include "../Libraries/GL.h"

#include <string>

namespace Video
{
	class Texture
	{
	public:
		// ctor
		Texture(std::string filePath, bool flipVertically = true);

		// dtor
		virtual ~Texture();

		// get the texture handle
		unsigned int GetTextureHandle() { return m_textureHandle; }

		// bind this texture
		void Bind();

	private:
		// the texture id
		GLuint m_textureHandle;
	};
}