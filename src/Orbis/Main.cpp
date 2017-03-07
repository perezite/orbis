#include <stdio.h>
#include <string>
#include <iostream>

#include "Core\Exception.h"
using namespace Core;

#include "Orbis\OrbisMain.h"
using namespace Orbis;

// reference: http://lazyfoo.net/tutorials/OpenGL/01_hello_opengl/index2.php
#undef main
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