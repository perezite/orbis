#ifndef _ORBIS_SDL_H
#define _ORBIS_SDL_H

// comment out this define to disable exceptions for SDL calls
#define SDL_CHECKS

#include "../../Base/System/Exception.h"
#include "../../Base/System/StringHelper.h"
using namespace System;

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>
#include <iostream>

void SDL_HandleError();

int SDL_Verify(int returnValue);

Sint64 SDL_Verify(Sint64 returnValue, Sint64 minimalAllowedValue);

SDL_RWops* SDL_Verify(SDL_RWops* returnValue);

#undef SDL_RWFromFile
#define SDL_RWFromFile(a, b) SDL_Verify(SDL_RWFromFile(a, b))

#define SDL_RWsize_old(ctx)		(ctx)->size(ctx)
#undef SDL_RWsize
#define SDL_RWsize(a) SDL_Verify(SDL_RWsize_old(a), -1)

#define SDL_RWclose_old(ctx)	(ctx)->close(ctx)
#undef SDL_RWclose
#define SDL_RWclose(file) SDL_Verify(SDL_RWclose_old(file))

namespace Libraries
{
	// wrapper class for SDL calls
	class SDL
	{
	public:
		// open a file
		static SDL_RWops* OpenFile(std::string filePath, std::string options);

		// get the file size
		// static Sint64 GetFileSize(SDL_RWops* file);

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

		// destroy the SDL window
		static void DestroyWindow(SDL_Window* window);

		// quit
		static void Quit();

		// init
		static void Init(Uint32 flags);

		// swap window with GL context
		static void GLSwapWindow(SDL_Window* window);

		// set attribute of GL context
		static void GLSetAttribute(SDL_GLattr attr, int value);
	};
}

#endif