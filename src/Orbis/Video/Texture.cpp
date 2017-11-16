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
		static SDL_Surface* img = IMG_Load(filePath.c_str());
		SDL_Surface* img2 = SDL_ConvertSurfaceFormat(img, SDL_PIXELFORMAT_ABGR8888, SDL_SWSURFACE);
		SDL_FreeSurface(img);
		img = img2;

		if (flipVertically)
		{
			SDL_Surface* flipped = GetFlippedSDLSurface(img);
			SDL_FreeSurface(img);
			img = flipped;
		}

		m_textureHandle = 0;
		glGenTextures(1, &m_textureHandle);
		glBindTexture(GL_TEXTURE_2D, m_textureHandle);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->w, img->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, img->pixels);
		SDL_FreeSurface(img);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_textureHandle);
	}

	void Texture::Bind()
	{
		glBindTexture(GL_TEXTURE_2D, m_textureHandle);
	}
}