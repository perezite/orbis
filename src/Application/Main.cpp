#include "Levels/Level1.h"
using namespace Levels;

#include "../Orbis/Orbis/OrbisMain.h"
#include "../Orbis/Core/LogHelper.h"
#include "../Orbis/GUI/GUIHelper.h"
#include "../Orbis/Game/LevelManager.h"
using namespace Orbis;
using namespace Core;
using namespace GUI;
using namespace Game;

#include "../Base/System/Exception.h"
using namespace System;

int main(int argc, char* args[])
{
	try
	{
		Level1* level1 = new Level1();
		LevelManager::GetInstance()->QueueLevel(level1);

		OrbisMain::GetInstance()->Run();
	}
	catch (Exception e)
	{
		LogHelper::LogMessage("%.1023s", e.what().c_str());
		GUIHelper::ShowMessageBox(e.what(), "Exception");
	}

	return 0;
}


