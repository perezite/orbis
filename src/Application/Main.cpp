#include "Sandbox/Sandbox.h"

#include "Levels/Level1.h"
using namespace Levels;

#include "../Orbis/Orbis/OrbisMain.h"
#include "../Orbis/Core/LogHelper.h"
#include "../Orbis/Game/LevelManager.h"
using namespace Orbis;
using namespace Core;
using namespace Game;

#include "../Base/System/Exception.h"
using namespace System;

#include <iostream>

int main(int argc, char* args[])
{	
	#ifdef __SANDBOX__
		run();
		return 0;
	#endif

	try
	{
		Level1* level1 = new Level1();
		LevelManager::GetInstance()->QueueLevel(level1);

		OrbisMain::GetInstance()->Run();
	}
	catch (Exception e)
	{
		LogHelper::LogMessage("%.1023s", e.what().c_str());
		LogHelper::ShowMessageBox(e.what(), "Exception");
		exit(0);
	}

	return 0;
}


