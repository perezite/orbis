#include "TextureAtlas.h"

#include "../../Base/System/Exception.h"

namespace Video
{
	const unsigned int TextureAtlas::MAX_EXTENT = 2048;

	TextureAtlas::TextureAtlas(std::vector<Texture*> textures)
	{
		AddRange(textures);
	}

	void TextureAtlas::AddRange(std::vector<Texture*> textures)
	{
		m_textures.insert(m_textures.begin(), textures.begin(), textures.end());

		// TODO: remove after implementation is finished
		Exception::Assert(m_textures.size() < 2, "Adding multiple textures to an atlas is not yet alloweds");
	}
}