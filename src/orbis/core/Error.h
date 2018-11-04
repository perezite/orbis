#pragma once

#include <string>

#ifdef _DEBUG
	#define ORB_ERROR(message) \
 		throw message;
#endif

#ifndef _DEBUG
	#define STRINGIFY(x) #x
	#define TOSTRING(x) STRINGIFY(x)
	#define AT __FILE__ ":" TOSTRING(__LINE__)
	#define ORB_ERROR(message) \
		orb::handleError(AT, message);
#endif

namespace orb
{
	#ifndef _DEBUG
		void handleError(std::string location, std::string message);
	#endif
}