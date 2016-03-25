#include <stdio.h>
#include <string>
#include <iostream>

#include "..\Orbis\Core\Exception.h"
using namespace Core;

#include "..\Orbis\Orbis\OrbisMain.h"
using namespace Orbis;

int main(int argc, char* args[])
{
	OrbisMain orbis(640, 480);

	try
	{
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
