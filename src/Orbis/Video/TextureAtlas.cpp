#include "TextureAtlas.h"

#include "../../Base/System/Exception.h"
#include "../../Base/Algorithms/BinPacking.h"
using namespace System;
using namespace Algorithms;

namespace Video
{
	TextureAtlas* TextureAtlas::GetInstance()
	{
		static TextureAtlas instance;
		return &instance;
	}

	void TextureAtlas::Add(Texture* texture)
	{
		m_textures.push_back(texture);
	}

	void TextureAtlas::Generate()
	{
		// compute the bin / page rect
		GLint pageSize;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &pageSize);
		Rect bin = Rect(0, 0, (float)pageSize, (float)pageSize);

		// pack the texture Rects
		std::vector<std::vector<Rect>> pageRectsCollection = BinPacking::Execute(bin, GetTextureRects());

		// create pages
		for (unsigned int i = 0; i < pageRectsCollection.size(); i++)
		{
			std::vector<Rect> pageRects = pageRectsCollection[i];
			std::vector<Texture*> pageTextures = SelectTextures(pageRects);
			TextureAtlasPage* page = new TextureAtlasPage(pageTextures, pageRects);
			m_pages.push_back(page);
		}
	}

	TextureAtlas::~TextureAtlas()
	{
		for (unsigned int i = 0; i < m_pages.size(); i++)
			delete m_pages[i];
	}

	std::vector<Rect> TextureAtlas::GetTextureRects()
	{
		std::vector<Rect> textureRects;

		for (unsigned int i = 0; i < m_textures.size(); i++)
		{
			Rect rect = ToOrbisRect(GetSurfaceRect(m_textures[i]->GetSurface()));
			rect.index = i;
			textureRects.push_back(rect);
		}

		return textureRects;
	}

	std::vector<Texture*> TextureAtlas::SelectTextures(std::vector<Rect> indexedRects)
	{
		std::vector<Texture*> textures;

		for (unsigned int i = 0; i < indexedRects.size(); i++)
		{
			unsigned int texIndex = indexedRects[i].index;
			textures.push_back(m_textures[texIndex]);
		}

		return textures;
	}

	SDL_Rect TextureAtlas::GetSurfaceRect(SDL_Surface* surface)
	{
		SDL_Rect rect;
		rect.x = 0; rect.y = 0; rect.h = surface->h; rect.w = surface->w;
		return rect;
	}

	Rect TextureAtlas::ToOrbisRect(SDL_Rect rect)
	{
		return Rect((float)rect.x, (float)rect.y, (float)rect.x + (float)rect.w, (float)rect.y + (float)rect.h);
	}
}

namespace Video
{
	TextureAtlasPage::TextureAtlasPage(std::vector<Texture*> textures, std::vector<Rect> rects)
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

	TextureAtlasPage::~TextureAtlasPage()
	{
		glDeleteTextures(1, &m_textureHandle);
	}

	void TextureAtlasPage::Bind()
	{
		glBindTexture(GL_TEXTURE_2D, m_textureHandle);
	}

	SDL_Rect TextureAtlasPage::ToSDLRect(Rect rect)
	{
		SDL_Rect sdlRect;
		sdlRect.x = (int)rect.GetLeft();
		sdlRect.y = (int)rect.GetBottom();
		sdlRect.w = (int)rect.GetWidth();
		sdlRect.h = (int)rect.GetHeight();

		return sdlRect;
	}

	Vector2D TextureAtlasPage::GetSmallestPowerOfTwoSize(std::vector<Rect> rects)
	{
		Rect boundary = GetBoundaryRect(rects);
		int potWidth = GetNextPowerOfTwo((int)boundary.GetWidth());
		int potHeight = GetNextPowerOfTwo((int)boundary.GetHeight());

		return Vector2D((float)potWidth, (float)potHeight);
	}

	Rect TextureAtlasPage::GetBoundaryRect(std::vector<Rect> rects)
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

	int TextureAtlasPage::GetNextPowerOfTwo(int number)
	{
		int pot = 1;
		while (pot < number)
			pot = 2 * pot;

		return pot;
	}

	void TextureAtlasPage::CopySurfaces(std::vector<Texture*> textures, std::vector<Rect> rects, SDL_Surface* pageSurface)
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

	void TextureAtlasPage::CreatePageTexture(SDL_Surface* surface)
	{
		glGenTextures(1, &m_textureHandle);
		glBindTexture(GL_TEXTURE_2D, m_textureHandle);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}

	SDL_Rect TextureAtlasPage::GetSurfaceRect(SDL_Surface * surface)
	{
		SDL_Rect rect;
		rect.x = 0; rect.y = 0; rect.h = surface->h; rect.w = surface->w;
		return rect;
	}

	void TextureAtlasPage::StoreUVRects(std::vector<Texture*> textures, std::vector<Rect> rects, SDL_Surface* surface)
	{
		float width = (float)surface->w;
		float height = (float)surface->h;

		for (unsigned int i = 0; i < textures.size(); i++)
		{
			Rect uvRect = Rect(rects[i].GetLeft() / width, rects[i].GetBottom() / height, rects[i].GetRight() / width, rects[i].GetTop() / height);
			m_uvRects.insert(std::make_pair(textures[i], uvRect));
		}
	}

	void TextureAtlasPage::RegisterTextures(std::vector<Texture*> textures)
	{
		for (unsigned int i = 0; i < textures.size(); i++)
		{
			textures[i]->SetTextureAtlasPage(this);
		}
	}
}