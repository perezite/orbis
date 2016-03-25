#include <stdio.h>
#include <string>
#include <iostream>

#include "..\Orbis\Core\Exception.h"
using namespace Core;

#include "..\Orbis\Orbis\OrbisMain.h"
using namespace Orbis;

#include "Levels\Level1.h"
using namespace Levels;

int main(int argc, char* args[])
{
	OrbisMain orbis(640, 480);

	try
	{
		Level *initialLevel = new Level1();
		orbis.QueueLevel(initialLevel);
		orbis.Run();
	}
	catch (Exception e)
	{
		std::cout << "An exception occured: " << std::endl;
		std::cout << e.what() << std::endl;
		std::cout.flush();
		std::cin.get();
	}

	return 0;
}
