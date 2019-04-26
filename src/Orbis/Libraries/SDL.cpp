#include "SDL.h"

#include <stdarg.h>

void SDL_HandleError()
{
	std::string error = std::string(SDL_GetError());
	error = error.empty() ? "Unknown error" : error;

	std::string message = "SDL Error: " + error;
	SDL_ClearError();
	throw Exception(message);
}

void IMG_HandleError()
{
	std::string error = std::string(IMG_GetError());
	error = error.empty() ? "Unknown error" : error;

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


size_t SDL_Verify(size_t result, size_t expected)
{
	if (result < expected)
		SDL_HandleError();

	return result;
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

SDL_Window* SDL_Verify(SDL_Window* returnValue)
{
	if (returnValue == NULL)
		SDL_HandleError();

	return returnValue;
}

SDL_GLContext SDL_Verify(SDL_GLContext returnValue)
{
	if (returnValue == NULL)
		SDL_HandleError();

	return returnValue;
}

SDL_Surface* IMG_Verify(SDL_Surface* returnValue)
{
	if (returnValue == NULL)
		IMG_HandleError();

	return returnValue;
}

int IMG_Verify_Flags(int returnValue, int flags)
{
	if ((returnValue & flags) != flags)
		IMG_HandleError();

	return returnValue;
}