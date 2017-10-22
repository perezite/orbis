#include "SDL.h"

#include "../../Base/System/StringHelper.h"
#include "../../Base/System/Exception.h"
using namespace System;

#include <stdarg.h>

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
	#ifdef NORMAL_SDL_CHECKS
		#define CHECK_SDL() \
			CheckSDLError();
		#else
		#define	SDL_VERIFY();
	#endif

	SDL_RWops* SDL::OpenFile(std::string filePath, std::string options)
	{
		SDL_RWops* result = SDL_RWFromFile(filePath.c_str(), "r");
		if (result == NULL)
			CHECK_SDL();
		return result;
	}

	Sint64 SDL::GetFileSize(SDL_RWops* file)
	{
		Sint64 size = SDL_RWsize(file);
		if (size < -2)
			CHECK_SDL();
		return size;
	}
	
	size_t SDL::ReadFromFile(SDL_RWops* file, void* dest, size_t size, size_t maxnum)
	{
		size_t sizeRead = SDL_RWread(file, dest, size, maxnum);
		if (sizeRead == 0)
			CHECK_SDL();
		return sizeRead;
	}

	void SDL::CloseFile(SDL_RWops* file)
	{
		if (SDL_RWclose(file) != 0) 
			CHECK_SDL();
	}

	void SDL::Log(const char* format, ...)
	{
		va_list args;
		va_start(args, format);
			Log(format, args);
		va_end(args);
	}

	void SDL::Log(const char* format, va_list args)
	{
		char buf[1024];
		vsnprintf(buf, 1024, format, args);
		SDL_Log("%s", buf);
	}

	void SDL::ShowSimpleMessageBox(const char* message, const char* title)
	{
		if (SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, message, NULL) != 0)
			CHECK_SDL();
	}

	Uint32 SDL::GetTicks(void)
	{
		return SDL_GetTicks();
	}

	int SDL::PollEvent(SDL_Event * event)
	{
		return SDL_PollEvent(event);
	}
	SDL_Surface* SDL::CreateRGBSurface(Uint32 flags, int width, int height, int depth, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask)
	{
		SDL_Surface* surface = SDL_CreateRGBSurface(flags, width, height, depth, Rmask, Gmask, Bmask, Amask);
		if (surface == NULL)
			CHECK_SDL();
		return surface;
	}

	void SDL::LockSurface(SDL_Surface* surface)
	{
		if (SDL_MUSTLOCK(surface))
		{
			if (SDL_LockSurface(surface) != 0)
				CHECK_SDL();
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
			CHECK_SDL();
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
			CHECK_SDL();
		return surface;
	}
}
