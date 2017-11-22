#include "Texture.h"

#include "../Libraries/SDL.h"
#include "../Core/AssetHelper.h"
using namespace Core;

namespace
{
	// flip an SDL surface
	SDL_Surface* GetFlippedSDLSurface(SDL_Surface* surface)
	{
		SDL_Surface *flipped = SDL_CreateRGBSurface(SDL_SWSURFACE, surface->w, surface->h, surface->format->BitsPerPixel,
			surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, surface->format->Amask);

		// lock
		if (SDL_MUSTLOCK(surface))
			SDL_LockSurface(surface);
		if (SDL_MUSTLOCK(flipped))
			SDL_LockSurface(flipped);

		// copy flipped
		for (int row = surface->h - 1; row >= 0; row--)
		{
			for (int col = 0; col < surface->w; col++)
			{
				size_t sourceOffset = row * surface->w + col;
				size_t sourceOffsetBytes = sourceOffset * surface->format->BytesPerPixel;
				size_t destOffset = (surface->h - row - 1) * surface->w + col;
				size_t destOffsetBytes = destOffset * surface->format->BytesPerPixel;

				memcpy((char*)flipped->pixels + destOffsetBytes, (char*)surface->pixels + sourceOffsetBytes, surface->format->BytesPerPixel);
			}
		}

		// unlock
		if (SDL_MUSTLOCK(surface))
			SDL_UnlockSurface(surface);
		if (SDL_MUSTLOCK(flipped))
			SDL_UnlockSurface(flipped);

		return flipped;
	}
}

namespace Video
{
	Texture::Texture(std::string assetPath, bool flipVertically)
	{
		std::string filePath = AssetHelper::AssetPathToFilePath(assetPath);
		m_surface = IMG_Load(filePath.c_str());
		SDL_Surface* surface2 = SDL_ConvertSurfaceFormat(m_surface, SDL_PIXELFORMAT_ABGR8888, SDL_SWSURFACE);
		SDL_FreeSurface(m_surface);
		m_surface = surface2;

		if (flipVertically)
		{
			SDL_Surface* flipped = GetFlippedSDLSurface(m_surface);
			SDL_FreeSurface(m_surface);
			m_surface = flipped;
		}

		glGenTextures(1, &m_textureHandle);
		glBindTexture(GL_TEXTURE_2D, m_textureHandle);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_surface->w, m_surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_surface->pixels);
		SDL_FreeSurface(m_surface);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		//m_surfaces.insert(m_surface);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_textureHandle);
		// m_surfaces.erase(m_surface);
	}

	void Texture::Bind()
	{
		glBindTexture(GL_TEXTURE_2D, m_textureHandle);
	}

	/*
	void Texture::DeleteAll()
	{
		std::set<SDL_Surface*>::iterator it;
		for (it = m_surfaces.begin(); it != m_surfaces.end(); ++it)
		{
			delete *it;
		}

		m_surfaces.clear();
	}*/
}