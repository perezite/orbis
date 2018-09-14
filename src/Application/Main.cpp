#include "Levels/Level1.h"
#include "Levels/Level2.h"
#include "Levels/Level3.h"
#include "Levels/Level4.h"
#include "Levels/Level5.h"
#include "Levels/Level6.h"
#include "Levels/Level7.h"
#include "Levels/Level8.h"
#include "Levels/Level9.h"
#include "Levels/Level10.h"
using namespace levels;

#include "../Orbis/Engine/OrbisMain.h"
#include "../Orbis/Core/LogHelper.h"
#include "../Orbis/Game/LevelManager.h"
#include "../Base/System/Exception.h"
using namespace orb::engine;
using namespace orb::core;
using namespace orb::game;
using namespace base::system;


int main(int argc, char* args[])
{	
	try
	{
		LevelManager::getInstance()->queueLevel(new Level1());
		OrbisMain::getInstance()->run();
	}
	catch (Exception e)
	{
		LogHelper::logMessage("%.1023s", e.what().c_str());

		#if defined(_DEBUG)
			throw e;
		#endif

 		LogHelper::showMessageBox(e.what(), "Exception");
	}

	return 0;
}
