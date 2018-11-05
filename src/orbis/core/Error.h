#pragma once

#include <string>

#define ORB_STRINGIFY(x) #x
#define ORB_TOSTRING(x) ORB_STRINGIFY(x)
#define ORB_AT __FILE__ ":" ORB_TOSTRING(__LINE__)

#ifdef _DEBUG
	#define ORB_ERROR(message)	\
 		throw message;			\
		orb::handleError(ORB_AT, message);
#endif

#ifndef _DEBUG
	#define ORB_ERROR(message) \
		orb::handleError(ORB_AT, message);
#endif

namespace orb
{
	void handleError(std::string location, std::string message);
}