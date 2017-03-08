#include "../Orbis/SDL_main.h"
#include "../Orbis/CheesyHelper.h"

#include "../Base/System/Exception.h"
using namespace System;

#include <iostream>

int main(int argc, char* args[])
{
	try
	{
		run(argc, args);
	}
	catch (Exception e)
	{
		char buffer[1024];
		sprintf(buffer, "%.1023s", e.what().c_str());
		CheesyHelper::Log(e.what().c_str());
	}

	return 0;
}
