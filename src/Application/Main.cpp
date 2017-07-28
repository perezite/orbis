#include "../Orbis/CheesyHelper.h"
#include "../Orbis/Orbis/OrbisMain.h"

#include "../Orbis/Video/VideoManager.h"
using namespace Video;

#include "../Base/System/Exception.h"
using namespace System;

#include <iostream>
#include <stdio.h>

ORBIS_MAIN()
{
	try
	{
		VideoManager::GetInstance()->Run();
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


