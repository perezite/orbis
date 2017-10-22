#pragma once

// comment out this define to disable exceptions for SDL calls
#define NORMAL_SDL_CHECKS

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>

namespace Libraries
{
	// wrapper class for SDL calls
	class SDL
	{
	public:
		// open a file
		static SDL_RWops* OpenFile(std::string filePath, std::string options);

		// get the file size
		static Sint64 GetFileSize(SDL_RWops* file);

		// read from file
		static size_t ReadFromFile(SDL_RWops* file, void* dest, size_t size, size_t maxnum);

		// close the file
		static void CloseFile(SDL_RWops* file);

		// log a message
		static void Log(const char* format, ...);

		// log a message
		static void Log(const char* format, va_list args);

		// show a message box
		static void ShowSimpleMessageBox(const char * message, const char * title);

		// get ticks
		static Uint32 GetTicks(void);

		// poll event
		static int PollEvent(SDL_Event *event);

		// create an rgb surface
		static SDL_Surface* CreateRGBSurface(Uint32 flags, int width, int height, int depth, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask);

		// lock a surface
		static void LockSurface(SDL_Surface* surface);
		
		// unlock a surface
		static void UnlockSurface(SDL_Surface * surface);

		// convert the surface format
		static SDL_Surface* ConvertSurfaceFormat(SDL_Surface* src, Uint32 pixel_format, Uint32 flags);

		// free a surface
		static void FreeSurface(SDL_Surface* surface);

		// load an image
		static SDL_Surface* LoadSurface(const char* path);
	};
}