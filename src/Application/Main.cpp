 #define APP_TEST

#include "../Base/Math/Vector2.h"

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
#include "Testing/TestSuite.h"
using namespace app;

#include "../Base/Base.h"
using namespace base;

#include "../Orbis/Engine/OrbisMain.h"
#include "../Orbis/Core/LogUtil.h"
#include "../Orbis/Game/LevelManager.h"
using namespace orb;

int main(int argc, char* args[])
{	
	try
	{
		#if defined(APP_TEST)
			TestSuite::run();
			return 0;
		#endif	

		LevelManager::instance()->queueLevel(new Level1());
		OrbisMain::instance()->run();
	}
	catch (Exception e)
	{
		LogUtil::logMessage("%.1023s", e.what().c_str());

		LogUtil::showMessageBox(e.what(), "Exception");

		#if defined(_DEBUG)
			throw e;
		#endif
	}

	return 0;
}