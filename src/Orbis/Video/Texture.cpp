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
		// load the image into an SDL surface
		m_surface = IMG_Load(m_filePath.c_str());
		if (!m_surface)
		{
			throw Exception("Loading the following texture file failed: " + m_filePath);
		}

		// blit the loaded surface into an auxiliary surface with known color settings
		#if SDL_BYTEORDER == SDL_BIG_ENDIAN
			Uint32 colorMasks[4] = { 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff };
		#else
			Uint32 colorMasks[4] = { 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000 };
		#endif
		SDL_Surface* auxiliarySurface = SDL_CreateRGBSurface(0, m_surface->w, m_surface->h, 32, colorMasks[0], colorMasks[1], colorMasks[2], colorMasks[3]);
		if (!auxiliarySurface)
			throw Exception("Creating the surface failed");
		SDL_Rect area = { 0, 0, m_surface->w, m_surface->h };
		if (SDL_BlitSurface(m_surface, &area, auxiliarySurface, &area) < 0)
			throw Exception("Blitting the surface failed");

		// create texture from surface
		m_textureId = m_highestTextureId + 1;
		m_highestTextureId = m_textureId;
		glGenTextures(1, &m_textureId);
		glBindTexture(GL_TEXTURE_2D, m_textureId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_surface->w, m_surface->h, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8_REV, auxiliarySurface->pixels);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		GraphicsAdapter::AssertNoError();

		// cleanup
		SDL_FreeSurface(auxiliarySurface);
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
