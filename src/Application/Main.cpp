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
using namespace Levels;

#include "../Orbis/Orbis/OrbisMain.h"
#include "../Orbis/Core/LogHelper.h"
#include "../Orbis/Game/LevelManager.h"
#include "../Base/System/Exception.h"
using namespace Orbis;
using namespace Core;
using namespace Game;
using namespace System;

#include <iostream>

#include "../Base/Serialization/JsonReader.h"
using namespace Serialization;

// #define DEBUG_JSON

#if defined(DEBUG_JSON)
void Test()
{
	std::string jsonStr = "{ {1.0f, {2.0f, 3.0f}}, {4.0f, {5.0f, 6.0f}} }";
	JsonReader reader(jsonStr);
	while (reader.getChild())
	{
		std::cout << reader.getFloat() << std::endl;
		reader.getChild();
		std::cout << reader.getFloat() << std::endl;
		std::cout << reader.getFloat() << std::endl;
	}
	std::cin.get();
}
#endif

int main(int argc, char* args[])
{	
#if defined DEBUG_JSON
	Test();

	return 0;

#else

	try
	{
		LevelManager::getInstance()->queueLevel(new Level8());
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

#endif

}
