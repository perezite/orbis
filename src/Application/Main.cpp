#include "../Orbis/Video/VideoManager.h"
#include "../Orbis/Core/LogHelper.h"
#include "../Orbis/GUI/GUIHelper.h"
using namespace Video;
using namespace Core;
using namespace GUI;

#include "../Base/System/Exception.h"
using namespace System;

#include <iostream>
#include <stdio.h>

int main(int argc, char* args[])
{
	try
	{
		VideoManager::GetInstance()->Run();
	}
	catch (Exception e)
	{
		LogHelper::LogMessage("%.1023s", e.what().c_str());
		GUIHelper::ShowMessageBox(e.what(), "Exception");
	}

	return 0;
}


