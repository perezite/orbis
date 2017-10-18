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

		// get the file size
		static SignedLong GetFileSize(File* file);

		// read from file
		static size_t ReadFromFile(File* file, void* dest, size_t size, size_t maxnum);

		// close the file
		static void CloseFile(File* file);

		// log a message
		static void Log(const char* format, ...);

		// log a message
		static void Log(const char* format, va_list args);
	};
}