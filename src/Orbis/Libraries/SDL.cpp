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
			throw Exception(message);
		}
	}

	// handle SDL exceptions
	#ifdef SDL_EXCEPTIONS
		#define SDL_VERIFY() \
			CheckSDLError();
		#else
		#define	SDL_VERIFY();
	#endif

	SDL::File* SDL::OpenFile(std::string filePath, std::string options)
	{
		File* result = SDL_RWFromFile(filePath.c_str(), "r");
		SDL_VERIFY();
		return result;
	}

	SDL::SignedLong SDL::GetFileSize(File * file)
	{
		SDL::SignedLong size = SDL_RWsize(file);
		SDL_VERIFY();
		return size;
	}
	
	size_t SDL::ReadFromFile(File * file, void* dest, size_t size, size_t maxnum)
	{
		size_t sizeRead = SDL_RWread(file, dest, size, maxnum);
		SDL_VERIFY();
		return sizeRead;
	}

	void SDL::CloseFile(File * file)
	{
		SDL_RWclose(file);
		SDL_VERIFY();
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
		SDL_VERIFY();
	}
}
