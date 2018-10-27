#ifndef _ORBIS_SDL_H
#define _ORBIS_SDL_H

#include "../../Base/Base.h"
using namespace base;

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>
#include <iostream>

void SDL_HandleError();

int SDL_Verify(int returnValue);

Sint64 SDL_Verify(Sint64 returnValue, Sint64 minimalAllowedValue);

SDL_RWops* SDL_Verify(SDL_RWops* returnValue);

SDL_Surface* SDL_Verify(SDL_Surface* returnValue);

SDL_Window* SDL_Verify(SDL_Window* returnValue);

SDL_GLContext SDL_Verify(SDL_GLContext  returnValue);

SDL_Surface* IMG_Verify(SDL_Surface* returnValue);

int IMG_Verify_Flags(int returnValue, int flags);

#define SDL_RWsize_old(ctx)		(ctx)->size(ctx)
#undef SDL_RWsize
#define SDL_RWsize(a) SDL_Verify(SDL_RWsize_old(a), -1)

#define SDL_RWclose_old(ctx)	(ctx)->close(ctx)
#undef SDL_RWclose
#define SDL_RWclose(file) SDL_Verify(SDL_RWclose_old(file))

#define SDL_RWwrite_old(ctx, ptr, size, n)	(ctx)->write(ctx, ptr, size, n)
#undef SDL_RWwrite
#define SDL_RWwrite(ctx, ptr, size, n) SDL_Verify(SDL_RWwrite_old(ctx, ptr, size, n), n)

#define SDL_RWFromFile_Checked(a, b) SDL_Verify(SDL_RWFromFile(a, b))

#define SDL_ShowSimpleMessageBox(flags, title, message, window) SDL_Verify(SDL_ShowSimpleMessageBox(flags, title, message, window))

#define SDL_CreateRGBSurface(flags, width, height, depth, rmask, gmask, bmask, amask) SDL_Verify(SDL_CreateRGBSurface(flags, width, height, depth, rmask, gmask, bmask, amask))

#define SDL_LockSurface(surface) SDL_Verify(SDL_LockSurface(surface))

#define SDL_ConvertSurfaceFormat(src, pixel_format, flags) SDL_Verify(SDL_ConvertSurfaceFormat(src, pixel_format, flags))

#define SDL_GL_SetAttribute(attr, value) SDL_Verify(SDL_GL_SetAttribute(attr, value))

#define SDL_CreateWindow(title, x, y, w, h, flags) SDL_Verify(SDL_CreateWindow(title, x, y, w, h, flags))

#define SDL_GL_CreateContext(window) SDL_Verify(SDL_GL_CreateContext(window))

#define SDL_GetDisplayMode(displayIndex, modeIndex, mode) SDL_Verify(SDL_GetDisplayMode(displayIndex, modeIndex, mode))

#define SDL_Init(flags) SDL_Verify(SDL_Init(flags))

#define SDL_BlitSurface_old SDL_UpperBlit
#undef SDL_BlitSurface
#define SDL_BlitSurface(a, b, c, d) SDL_Verify(SDL_BlitSurface_old(a, b, c, d))

#define SDL_GetSurfaceBlendMode(a, b) SDL_Verify(SDL_GetSurfaceBlendMode(a, b))

#define SDL_SetSurfaceBlendMode(a, b) SDL_Verify(SDL_SetSurfaceBlendMode(a, b))

#define IMG_Load(path) IMG_Verify(IMG_Load(path))

#define IMG_Init(flags) IMG_Verify_Flags(IMG_Init(flags), flags)

#endif