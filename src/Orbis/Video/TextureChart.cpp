#include "TextureChart.h"

#include "../../Base/Base.h"
using namespace base;

namespace orb
{
	TextureChart::TextureChart(const std::vector<Texture*>& textures, const std::vector<Rect>& rects)
	{
		SDL_Surface* surface = createChartSurface(textures, rects);
		copyTextureDataToSurface(textures, rects, surface);
		m_uvRects = computeUVRects(textures, rects, surface);
		copyChartSurfaceDataToOpenGl(surface);
		SDL_FreeSurface(surface);
		registerTextures(textures);
	}

	TextureChart::~TextureChart()
	{
		glDeleteTextures(1, &m_textureHandle);
	}

	const Rect& TextureChart::getUVRect(Texture* tex) const
	{
		return m_uvRects.find(tex)->second;
	}

	void TextureChart::bind()
	{
		glBindTexture(GL_TEXTURE_2D, m_textureHandle);
	}

	SDL_Surface* TextureChart::createChartSurface(const std::vector<Texture*>& textures, const std::vector<Rect>& rects)
	{
		Vector2f nextPotSize = getNextLargerPowerOfTwoRect(getBoundaryRect(rects)).getSize();
		SDL_Surface* surface = textures[0]->getSurface();
		SDL_PixelFormat* format = surface->format;
		return SDL_CreateRGBSurface(surface->flags, (int)nextPotSize.x, (int)nextPotSize.y, format->BitsPerPixel,
			format->Rmask, format->Gmask, format->Bmask, format->Amask);
	}

	void TextureChart::copyTextureDataToSurface(const std::vector<Texture*>& textures, const std::vector<Rect>& rects, SDL_Surface* surface)
	{
		for (unsigned int i = 0; i < textures.size(); i++) {
			SDL_Rect sourceRect = getSurfaceRect(textures[i]->getSurface());
			SDL_Rect targetRect = toSdlRect(rects[i]);
			SDL_BlendMode origBlendMode;
			SDL_GetSurfaceBlendMode(textures[i]->getSurface(), &origBlendMode);
			SDL_SetSurfaceBlendMode(textures[i]->getSurface(), SDL_BLENDMODE_NONE);
			SDL_BlitSurface(textures[i]->getSurface(), &sourceRect, surface, &targetRect);
			SDL_SetSurfaceBlendMode(textures[i]->getSurface(), origBlendMode);
		}
	}

	const std::map<Texture*, Rect> TextureChart::computeUVRects(const std::vector<Texture*>& textures, const std::vector<Rect>& rects, SDL_Surface* surface)
	{
		std::map<Texture*, Rect> uvRects;
		float width = (float)surface->w, height = (float)surface->h;

		for (unsigned int i = 0; i < textures.size(); i++) {
			Rect uvRect = Rect(rects[i].getLeft() / width, rects[i].getBottom() / height, rects[i].getRight() / width, rects[i].getTop() / height);
			uvRects.insert(std::make_pair(textures[i], uvRect));
		}

		return uvRects;
	}

	void TextureChart::copyChartSurfaceDataToOpenGl(SDL_Surface* surface)
	{
		glGenTextures(1, &m_textureHandle);
		glBindTexture(GL_TEXTURE_2D, m_textureHandle);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}

	void TextureChart::registerTextures(const std::vector<Texture*>& textures)
	{
		for (unsigned int i = 0; i < textures.size(); i++)
			textures[i]->setParentChart(this);
	}

	const Rect TextureChart::getNextLargerPowerOfTwoRect(const Rect& rect)
	{
		int width = MathUtil::nextPowerOfTwo((int)rect.getWidth());
		int height = MathUtil::nextPowerOfTwo((int)rect.getHeight());
		return Rect(0, 0, (float)width, (float)height);
	}

	const SDL_Rect TextureChart::getSurfaceRect(const SDL_Surface* surface)
	{
		return SDL_Rect{ 0, 0, surface->w, surface->h };
	}

	const SDL_Rect TextureChart::toSdlRect(const Rect& rect)
	{
		return SDL_Rect{ (int)rect.getLeft(), (int)rect.getBottom(), (int)rect.getWidth(), (int)rect.getHeight() };
	}

	const Rect TextureChart::getBoundaryRect(const std::vector<Rect>& rects)
	{
		Vector2f max(0, 0);
		for (unsigned int i = 0; i < rects.size(); i++) {
			if (rects[i].getRight() > max.x)
				max.x = rects[i].getRight();
			if (rects[i].getTop() > max.y)
				max.y = rects[i].getTop();
		}

		return Rect(0, 0, max.x, max.y);
	}
}