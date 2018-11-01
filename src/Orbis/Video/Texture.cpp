#include "Texture.h"

#include "TextureAtlas.h"

#include "../Libraries/SDL.h"
#include "../Core/AssetUtil.h"
#include "../Video/VideoManager.h"

namespace orb
{
	Texture::Texture(const std::string& assetPath, bool flipVertically) : m_assetPath(assetPath), m_handle(0), m_parentChart(NULL)
	{
		// load 
		std::string filePath = AssetUtil::assetPathToFilePath(assetPath);
		m_surface = IMG_Load(filePath.c_str());

		// convert and flip
		m_surface = convertPixelFormat(m_surface, SDL_PIXELFORMAT_ABGR8888);
		if (flipVertically)
			m_surface = flipSurfaceVertically(m_surface);

		// create opengl texture
		glGenTextures(1, &m_handle);
		glBindTexture(GL_TEXTURE_2D, m_handle);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_surface->w, m_surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_surface->pixels);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}

	Texture::~Texture()
	{
		if (!m_parentChart) {
			glDeleteTextures(1, &m_handle);
			SDL_FreeSurface(m_surface);
		}
	}

	Vector2f Texture::computeChartedUV(const Vector2f& texUV)
	{
		if (m_parentChart) {
			Rect uvRect = m_parentChart->getUVRect(this);
			Vector2f atlasUV(uvRect.getLeft() + texUV.x * uvRect.getWidth(), uvRect.getBottom() + texUV.y * uvRect.getHeight());
			return atlasUV;
		}
		else
			return texUV;
	}

	void Texture::bind()
	{
		if (m_parentChart)
			m_parentChart->bind();
		else
			glBindTexture(GL_TEXTURE_2D, m_handle);
	}

	SDL_Surface* Texture::convertPixelFormat(SDL_Surface* surface, Uint32 pixelFormat)
	{
		SDL_Surface* converted = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_ABGR8888, SDL_SWSURFACE);
		SDL_FreeSurface(surface);
		return converted;
	}

	SDL_Surface* Texture::flipSurfaceVertically(SDL_Surface* surface)
	{
		SDL_Surface *flipped = SDL_CreateRGBSurface(SDL_SWSURFACE, surface->w, surface->h, surface->format->BitsPerPixel,
			surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, surface->format->Amask);

		// lock
		if (SDL_MUSTLOCK(flipped))
			SDL_LockSurface(flipped);

		// flip
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
		if (SDL_MUSTLOCK(flipped))
			SDL_UnlockSurface(flipped);

		// cleanup
		SDL_FreeSurface(surface);

		return flipped;
	}
}