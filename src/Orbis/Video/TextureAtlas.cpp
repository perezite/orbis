#include "TextureAtlas.h"

#include "../Libraries/GL.h"

#include "../../Base/System/Exception.h"
using namespace System;

namespace Video
{
	TextureAtlasPage::TextureAtlasPage()
	{
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &m_maxSize);
	}
}

namespace Video
{
	TextureAtlas * TextureAtlas::GetInstance()
	{
		static TextureAtlas instance;
		return &instance;
	}

	void TextureAtlas::Add(Texture * texture)
	{
		// TODO: remove later
		static int count = 0;

		Exception::Assert(count == 0, "Not yet supported");
		count++;
	}

	void TextureAtlas::Generate()
	{
		std::cout << "TextureAtlas::Generate()" << std::endl;
	}
}