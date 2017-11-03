#include "SDL.h"

#include <stdarg.h>

void SDL_HandleError()
{
	std::string error = std::string(SDL_GetError());
	error = StringHelper::IsEmpty(error) ? "Unknown error" : error;

	std::string message = "SDL Error: " + error;
	SDL_ClearError();
	throw Exception(message);
}

void IMG_HandleError()
{
	std::string error = std::string(IMG_GetError());
	error = StringHelper::IsEmpty(error) ? "Unknown error" : error;

	std::string message = "SDL Image Error: " + error;
	SDL_ClearError();
	throw Exception(message);
}

int SDL_Verify(int returnValue)
{
	if (returnValue != 0)
		SDL_HandleError();

	return returnValue;
}

Sint64 SDL_Verify(Sint64 returnValue, Sint64 minimalAllowedValue)
{
	if (returnValue < minimalAllowedValue)
		SDL_HandleError();

	return returnValue;
}

SDL_RWops* SDL_Verify(SDL_RWops* returnValue)
{
	if (returnValue == NULL)
		SDL_HandleError();

	return returnValue;
}

SDL_Surface * SDL_Verify(SDL_Surface * returnValue)
{
	if (returnValue == NULL)
		SDL_HandleError();

	return returnValue;
}

SDL_Surface * IMG_Verify(SDL_Surface * returnValue)
{
	if (returnValue == NULL)
		IMG_HandleError();

	return returnValue;
}

namespace Libraries
{
	// handle SDL exceptions
	void CheckSDLError()
	{
		std::string error = std::string(SDL_GetError());

		if (!StringHelper::IsEmpty(error))
		{
			std::string message = "SDL Error: " + error;
			SDL_ClearError();
			throw Exception(message);
		}
	}

	// handle SDL exceptions
	#ifdef SDL_CHECKS
		#define SDL_CHECK() \
			CheckSDLError();
		#else
		#define	SDL_VERIFY();
	#endif

	SDL_RWops* SDL::OpenFile(std::string filePath, std::string options)
	{
		SDL_RWops* result = SDL_RWFromFile(filePath.c_str(), "r");
		if (result == NULL)
			SDL_CHECK();
		return result;
	}

	/*
	Sint64 SDL::GetFileSize(SDL_RWops* file)
	{
		Sint64 size = SDL_RWsize(file);
		if (size < -2)
			SDL_CHECK();
		return size;
	}*/
	
	size_t SDL::ReadFromFile(SDL_RWops* file, void* dest, size_t size, size_t maxnum)
	{
		size_t sizeRead = SDL_RWread(file, dest, size, maxnum);
		if (sizeRead == 0)
			SDL_CHECK();
		return sizeRead;
	}

	void SDL::CloseFile(SDL_RWops* file)
	{
		if (SDL_RWclose(file) != 0) 
			SDL_CHECK();
	}

	Uint32 SDL::GetTicks(void)
	{
		return SDL_GetTicks();
	}

	SDL_Surface* SDL::CreateRGBSurface(Uint32 flags, int width, int height, int depth, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask)
	{
		SDL_Surface* surface = SDL_CreateRGBSurface(flags, width, height, depth, Rmask, Gmask, Bmask, Amask);
		if (surface == NULL)
			SDL_CHECK();
		return surface;
	}

	void SDL::LockSurface(SDL_Surface* surface)
	{
		if (SDL_MUSTLOCK(surface))
		{
			if (SDL_LockSurface(surface) != 0)
				SDL_CHECK();
		}
	}

	void SDL::UnlockSurface(SDL_Surface* surface)
	{
		if (SDL_MUSTLOCK(surface))
			SDL_UnlockSurface(surface);
	}
	
	SDL_Surface * SDL::ConvertSurfaceFormat(SDL_Surface * src, Uint32 pixel_format, Uint32 flags)
	{
		SDL_Surface* surface = SDL_ConvertSurfaceFormat(src, pixel_format, flags);
		if (surface == NULL)
			SDL_CHECK();
		return surface;
	}

	void SDL::FreeSurface(SDL_Surface * surface)
	{
		SDL_FreeSurface(surface);
	}

	SDL_Surface* SDL::LoadSurface(const char* path)
	{
		SDL_Surface* surface = IMG_Load(path);
		if (surface == NULL)
			SDL_CHECK();
		return surface;
	}

	void SDL::DestroyWindow(SDL_Window* window)
	{
		SDL_DestroyWindow(window);
		SDL_CHECK();
	}

	void SDL::Quit()
	{
		SDL_Quit();
		SDL_CHECK();
	}

	void SDL::Init(Uint32 flags)
	{
		if (SDL_Init(flags) != 0)
			SDL_CHECK();
	}

	void SDL::GLSwapWindow(SDL_Window * window)
	{
		SDL_GL_SwapWindow(window);
	}

	void SDL::GLSetAttribute(SDL_GLattr attr, int value)
	{

	}
}
