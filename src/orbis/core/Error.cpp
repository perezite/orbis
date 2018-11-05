#include "Error.h"
#include "Log.h"

#include <stdlib.h>

namespace orb
{
	void handleError(std::string location, std::string message)
	{
		Log().error() << location << ": " << message;
		#ifndef DEBUG
			Log().errorMessageBox("Error") << location << ": " << message;
		#endif

		exit(0);
	}
}

