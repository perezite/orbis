#include "Sandboxing/Sandbox.h"
#include "Sandboxing/Bootbox.h"
#include "Levels/Level1.h"
#include "Levels/Level2.h"
#include "Levels/Level3.h"
#include "Levels/Level4.h"
#include "Levels/Level5.h"
using namespace Levels;
using namespace Sandboxing;

#include "../Orbis/Orbis/OrbisMain.h"
#include "../Orbis/Core/LogHelper.h"
#include "../Orbis/Game/LevelManager.h"
#include "../Base/System/Exception.h"
using namespace Orbis;
using namespace Core;
using namespace Game;
using namespace System;

#include <iostream>

int main(int argc, char* args[])
{	
	#ifdef __SANDBOX__
		Bootbox::Run();
		return 0;
	#endif

	try
	{
		OrbisMain::GetInstance()->Initialize();
		
		Level5* level = new Level5();
		LevelManager::GetInstance()->QueueLevel(level);

		OrbisMain::GetInstance()->Run();
	}
	catch (Exception e)
	{
		LogHelper::LogMessage("%.1023s", e.what().c_str());

		#if defined(_DEBUG)
			throw e;
		#endif

		LogHelper::ShowMessageBox(e.what(), "Exception");
	}

	return 0;
}


