#include "TextureChart.h"

namespace Video
{
	TextureChart::TextureChart(std::vector<Texture*> textures, std::vector<Rect> rects)
	{
		// create a page surface with the smallest possible power of two size
		Vector2D potSize = getSmallestPowerOfTwoSize(rects);
		SDL_Surface* texSurface = textures[0]->getSurface();
		SDL_PixelFormat* texFormat = texSurface->format;
		SDL_Surface* surface = SDL_CreateRGBSurface(texSurface->flags, (int)potSize.x, (int)potSize.y,
			texFormat->BitsPerPixel, texFormat->Rmask, texFormat->Gmask, texFormat->Bmask, texFormat->Amask);

		copySurfaces(textures, rects, surface);

		createPageTexture(surface);

		storeUVRects(textures, rects, surface);

		registerTextures(textures);

		// cleanup
		SDL_FreeSurface(surface);
		for (unsigned int i = 0; i < textures.size(); i++)
		{
			GLuint handle = textures[i]->getHandle();
			glDeleteTextures(1, &handle);
			SDL_FreeSurface(textures[i]->getSurface());
		}
	}

	TextureChart::~TextureChart()
	{
		glDeleteTextures(1, &m_textureHandle);
	}

	void TextureChart::bind()
	{
		glBindTexture(GL_TEXTURE_2D, m_textureHandle);
	}

	SDL_Rect TextureChart::toSDLRect(Rect rect)
	{
		SDL_Rect sdlRect;
		sdlRect.x = (int)rect.getLeft();
		sdlRect.y = (int)rect.getBottom();
		sdlRect.w = (int)rect.getWidth();
		sdlRect.h = (int)rect.getHeight();

		return sdlRect;
	}

	Vector2D TextureChart::getSmallestPowerOfTwoSize(std::vector<Rect> rects)
	{
		Rect boundary = getBoundaryRect(rects);
		int potWidth = getNextPowerOfTwo((int)boundary.getWidth());
		int potHeight = getNextPowerOfTwo((int)boundary.getHeight());

		return Vector2D((float)potWidth, (float)potHeight);
	}

	Rect TextureChart::getBoundaryRect(std::vector<Rect> rects)
	{
		// get maximal x and y coordinates in packed rects
		Vector2D max(0, 0);
		for (unsigned int i = 0; i < rects.size(); i++)
		{
			if (rects[i].getRight() > max.x)
				max.x = rects[i].getRight();
			if (rects[i].getTop() > max.y)
				max.y = rects[i].getTop();
		}

		return Rect(0, 0, max.x, max.y);
	}

	int TextureChart::getNextPowerOfTwo(int number)
	{
		int pot = 1;
		while (pot < number)
			pot = 2 * pot;

		return pot;
	}

	void TextureChart::copySurfaces(std::vector<Texture*> textures, std::vector<Rect> rects, SDL_Surface* pageSurface)
	{
		// copy the original textures into the page surface
		for (unsigned int i = 0; i < textures.size(); i++)
		{
			SDL_Rect sourceRect = getSurfaceRect(textures[i]->getSurface());
			SDL_Rect targetRect = toSDLRect(rects[i]);
			SDL_BlendMode origBlendMode;
			SDL_GetSurfaceBlendMode(textures[i]->getSurface(), &origBlendMode);
			SDL_SetSurfaceBlendMode(textures[i]->getSurface(), SDL_BLENDMODE_NONE);
			SDL_BlitSurface(textures[i]->getSurface(), &sourceRect, pageSurface, &targetRect);
			SDL_SetSurfaceBlendMode(textures[i]->getSurface(), origBlendMode);
		}
	}

	void TextureChart::createPageTexture(SDL_Surface* surface)
	{
		glGenTextures(1, &m_textureHandle);
		glBindTexture(GL_TEXTURE_2D, m_textureHandle);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}

	SDL_Rect TextureChart::getSurfaceRect(SDL_Surface * surface)
	{
		SDL_Rect rect;
		rect.x = 0; rect.y = 0; rect.h = surface->h; rect.w = surface->w;
		return rect;
	}

	void TextureChart::storeUVRects(std::vector<Texture*> textures, std::vector<Rect> rects, SDL_Surface* surface)
	{
		float width = (float)surface->w;
		float height = (float)surface->h;

		for (unsigned int i = 0; i < textures.size(); i++)
		{
			Rect uvRect = Rect(rects[i].getLeft() / width, rects[i].getBottom() / height, rects[i].getRight() / width, rects[i].getTop() / height);
			m_uvRects.insert(std::make_pair(textures[i], uvRect));
		}
	}

	void TextureChart::registerTextures(std::vector<Texture*> textures)
	{
		for (unsigned int i = 0; i < textures.size(); i++)
		{
			textures[i]->setTextureAtlasPage(this);
		}
	}
}