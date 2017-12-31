#include "TextureChart.h"

namespace Video
{
	TextureChart::TextureChart(std::vector<Texture*> textures, std::vector<Rect> rects)
	{
		// create a page surface with the smallest possible power of two size
		Vector2D potSize = GetSmallestPowerOfTwoSize(rects);
		SDL_Surface* texSurface = textures[0]->GetSurface();
		SDL_PixelFormat* texFormat = texSurface->format;
		SDL_Surface* surface = SDL_CreateRGBSurface(texSurface->flags, (int)potSize.x, (int)potSize.y,
			texFormat->BitsPerPixel, texFormat->Rmask, texFormat->Gmask, texFormat->Bmask, texFormat->Amask);

		CopySurfaces(textures, rects, surface);

		CreatePageTexture(surface);

		StoreUVRects(textures, rects, surface);

		RegisterTextures(textures);

		// cleanup
		SDL_FreeSurface(surface);
		for (unsigned int i = 0; i < textures.size(); i++)
			SDL_FreeSurface(textures[i]->GetSurface());
	}

	TextureChart::~TextureChart()
	{
		glDeleteTextures(1, &m_textureHandle);
	}

	void TextureChart::Bind()
	{
		glBindTexture(GL_TEXTURE_2D, m_textureHandle);
	}

	SDL_Rect TextureChart::ToSDLRect(Rect rect)
	{
		SDL_Rect sdlRect;
		sdlRect.x = (int)rect.GetLeft();
		sdlRect.y = (int)rect.GetBottom();
		sdlRect.w = (int)rect.GetWidth();
		sdlRect.h = (int)rect.GetHeight();

		return sdlRect;
	}

	Vector2D TextureChart::GetSmallestPowerOfTwoSize(std::vector<Rect> rects)
	{
		Rect boundary = GetBoundaryRect(rects);
		int potWidth = GetNextPowerOfTwo((int)boundary.GetWidth());
		int potHeight = GetNextPowerOfTwo((int)boundary.GetHeight());

		return Vector2D((float)potWidth, (float)potHeight);
	}

	Rect TextureChart::GetBoundaryRect(std::vector<Rect> rects)
	{
		// get maximal x and y coordinates in packed rects
		Vector2D max(0, 0);
		for (unsigned int i = 0; i < rects.size(); i++)
		{
			if (rects[i].GetRight() > max.x)
				max.x = rects[i].GetRight();
			if (rects[i].GetTop() > max.y)
				max.y = rects[i].GetTop();
		}

		return Rect(0, 0, max.x, max.y);
	}

	int TextureChart::GetNextPowerOfTwo(int number)
	{
		int pot = 1;
		while (pot < number)
			pot = 2 * pot;

		return pot;
	}

	void TextureChart::CopySurfaces(std::vector<Texture*> textures, std::vector<Rect> rects, SDL_Surface* pageSurface)
	{
		// copy the original textures into the page surface
		for (unsigned int i = 0; i < textures.size(); i++)
		{
			SDL_Rect sourceRect = GetSurfaceRect(textures[i]->GetSurface());
			SDL_Rect targetRect = ToSDLRect(rects[i]);
			SDL_BlendMode origBlendMode;
			SDL_GetSurfaceBlendMode(textures[i]->GetSurface(), &origBlendMode);
			SDL_SetSurfaceBlendMode(textures[i]->GetSurface(), SDL_BLENDMODE_NONE);
			SDL_BlitSurface(textures[i]->GetSurface(), &sourceRect, pageSurface, &targetRect);
			SDL_SetSurfaceBlendMode(textures[i]->GetSurface(), origBlendMode);
		}
	}

	void TextureChart::CreatePageTexture(SDL_Surface* surface)
	{
		glGenTextures(1, &m_textureHandle);
		glBindTexture(GL_TEXTURE_2D, m_textureHandle);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}

	SDL_Rect TextureChart::GetSurfaceRect(SDL_Surface * surface)
	{
		SDL_Rect rect;
		rect.x = 0; rect.y = 0; rect.h = surface->h; rect.w = surface->w;
		return rect;
	}

	void TextureChart::StoreUVRects(std::vector<Texture*> textures, std::vector<Rect> rects, SDL_Surface* surface)
	{
		float width = (float)surface->w;
		float height = (float)surface->h;

		for (unsigned int i = 0; i < textures.size(); i++)
		{
			Rect uvRect = Rect(rects[i].GetLeft() / width, rects[i].GetBottom() / height, rects[i].GetRight() / width, rects[i].GetTop() / height);
			m_uvRects.insert(std::make_pair(textures[i], uvRect));
		}
	}

	void TextureChart::RegisterTextures(std::vector<Texture*> textures)
	{
		for (unsigned int i = 0; i < textures.size(); i++)
		{
			textures[i]->SetTextureAtlasPage(this);
		}
	}
}