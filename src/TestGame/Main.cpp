#include "..\Base\System\Exception.h"
#include "..\Base\System\EnvironmentHelper.h"
using namespace System;

#include "Application\App.h"
using namespace Application;

int main(int argc, char* args[])
{
	try
	{
		App app;
		app.Run();
	}
	catch (Exception e)
	{
		std::cout << "An exception occured: " << std::endl;
		std::cout << e.what() << std::endl;
		std::cout.flush();
		std::cin.get();
	}

}