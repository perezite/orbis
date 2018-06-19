#include "Texture.h"

#include "TextureAtlas.h"

#include "../Libraries/SDL.h"
#include "../Core/AssetHelper.h"
#include "../Video/VideoManager.h"
using namespace Core;
using namespace Video;

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
		m_assetPath = assetPath;

		std::string filePath = AssetHelper::AssetPathToFilePath(assetPath);
		m_surface = IMG_Load(filePath.c_str());
		SDL_Surface* converted = SDL_ConvertSurfaceFormat(m_surface, SDL_PIXELFORMAT_ABGR8888, SDL_SWSURFACE);
		SDL_FreeSurface(m_surface);
		m_surface = converted;

		if (flipVertically)
		{
			SDL_Surface* flipped = GetFlippedSDLSurface(m_surface);
			SDL_FreeSurface(m_surface);
			m_surface = flipped;
		}

		glGenTextures(1, &m_handle);
		glBindTexture(GL_TEXTURE_2D, m_handle);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_surface->w, m_surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_surface->pixels);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		
		if (UsesAtlassing())
		{
			VideoManager::getInstance()->getTextureAtlas()->Add(this);
		}
	}

	Texture::~Texture()
	{
		if (!UsesAtlassing())
		{
			glDeleteTextures(1, &m_handle);
			SDL_FreeSurface(m_surface);
		}
	}

	Vector2D Texture::MapUVCoord(Vector2D texUV)
	{
		if (UsesAtlassing())
		{
			Rect uvRect = m_atlasChart->GetUVRect(this);
			Vector2D atlasUV(uvRect.GetLeft() + texUV.x * uvRect.GetWidth(), uvRect.GetBottom() + texUV.y * uvRect.GetHeight());
			return atlasUV;
		}
		else
		{
			return texUV;
		}
	}

	void Texture::Bind()
	{
		if (UsesAtlassing())
		{
			m_atlasChart->Bind();
		}
		else
		{
			glBindTexture(GL_TEXTURE_2D, m_handle);
		}
	}

	bool Texture::UsesAtlassing() const
	{
		#ifdef ORBIS_USE_TEXTURE_ATLASSING
			return true;
		#else
			return false;
		#endif
	}
}