#include "SandboxRunner.h"

#include <iostream>

namespace Sandbox
{
	void SandboxRunner::Run()
	{
		std::cout << "Run()" << std::endl;
		getchar();
	}
}