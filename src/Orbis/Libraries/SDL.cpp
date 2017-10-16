#include "SDL.h"

#include "../../Base/System/StringHelper.h"
#include "../../Base/System/Exception.h"
using namespace System;

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
}
