#include "Texture.h"
#include "GraphicsAdapter.h"

#include "..\Core\Exception.h"
using namespace Core;

#include <SDL_image.h>

namespace Video
{
	GLuint Texture::m_highestTextureId = -1;

	Texture::Texture(std::string filePath) : m_filePath(filePath)
	{
		// load the surface
		m_surface = IMG_Load(m_filePath.c_str());
		if (!m_surface)
		{
			throw Exception("Loading the following texture file failed: " + m_filePath);
		}

		// create texture from surface
		m_textureId = m_highestTextureId + 1;
		m_highestTextureId = m_textureId;
		glGenTextures(1, &m_textureId);
		glBindTexture(GL_TEXTURE_2D, m_textureId);
		int colorMode = m_surface->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB;
		glTexImage2D(GL_TEXTURE_2D, 0, colorMode, m_surface->w, m_surface->h, 0, colorMode, GL_UNSIGNED_BYTE, m_surface->pixels);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		GraphicsAdapter::AssertNoError();

		SDL_FreeSurface(m_surface);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_textureId);
			
		if (m_textureId == m_highestTextureId)
			m_highestTextureId = m_highestTextureId - 1;
	}

	void Texture::SetActive()
	{
		glBindTexture(GL_TEXTURE_2D, m_textureId);
	}
}
