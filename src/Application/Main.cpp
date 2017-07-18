#include "../Orbis/SDL_main.h"
#include "../Orbis/CheesyHelper.h"

#include "../Base/System/Exception.h"
using namespace System;

#include <iostream>
#include <stdio.h>

int main(int argc, char* args[])
{
	try
	{
		run(argc, args);
	}
	catch (Exception e)
	{
		char buffer[1024];
		snprintf(buffer, 1024, "%.1023s", e.what().c_str());
		CheesyHelper::Log(e.what().c_str());
		CheesyHelper::ShowMessageBox("Exception", e.what());
	}

	return 0;
}
