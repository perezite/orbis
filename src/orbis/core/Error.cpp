#include "Error.h"
#include "Log.h"

#include <stdlib.h>

namespace orb
{
	#ifndef _DEBUG
		void handleError(std::string location, std::string message)
		{
			Log().error() << location << ": " << message;
			std::cin.get();
			exit(0);
		}
	#endif

	void dummy()
	{
	}
}

