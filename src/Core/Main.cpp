#include <stdio.h>
#include <string>
#include <iostream>

#include "..\Base\Exception.h"
#include "..\Video\VideoSystem.h"

using namespace Video;

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

void run()
{
	VideoSystem videoSystem(640, 480);

	videoSystem.Run();
}

// reference: http://lazyfoo.net/tutorials/OpenGL/01_hello_opengl/index2.php
#undef main
int main(int argc, char* args[])
{
	try
	{
		run();
	}
	catch (Exception e)
	{
		std::cout << e.what() << std::endl;
		std::cin.get();
	}

	return 0;
}
