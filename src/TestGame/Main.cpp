#include <iostream>

#include "..\Base\System\Exception.h"
#include "..\Base\System\EnvironmentHelper.h"
using namespace System;

#include "..\Orbis\Orbis\OrbisMain.h"
using namespace Orbis;

#include "Levels\Level1.h"
using namespace Levels;

#include "..\Orbis\Game\LevelManager.h"
using namespace Game;

int main(int argc, char* args[])
{
	try
	{
		OrbisMain orbis(800, 400);

		Level *level1 = new Level1();
		LevelManager::GetInstance()->QueueLevel(level1);
		orbis.Run();
	}
	catch (Exception e)
	{
		std::cout << "An exception occured: " << std::endl;
		std::cout << e.what() << std::endl;
		std::cout.flush();
		std::cin.get();
	}

}