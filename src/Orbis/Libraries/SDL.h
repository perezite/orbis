#pragma once

// comment out this define to disable exceptions for GL calls
#define SDL_EXCEPTIONS

#include <SDL2/SDL.h>

#include <string>

namespace Libraries
{
	// wrapper class for SDL calls
	class SDL
	{
	public: 
		// an sdl file handle
		typedef SDL_RWops File;

		// a signed long integer for file sizes
		typedef Sint64 SignedLong;

	public:
		// open a file
		static File* OpenFile(std::string filePath, std::string options);
	};
}