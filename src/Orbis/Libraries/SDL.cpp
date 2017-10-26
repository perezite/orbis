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

	Sint64 SDL::GetFileSize(SDL_RWops* file)
	{
		Sint64 size = SDL_RWsize(file);
		if (size < -2)
			SDL_CHECK();
		return size;
	}
	
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
			SDL_CHECK();
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
