#include "BrickInspector.h"

#include <iostream>

namespace orb
{
	namespace inspectors
	{
		void BrickInspector::start()
		{
			std::cout << "BrickInspector::start()" << std::endl;
		}

		void BrickInspector::update()
		{
			std::cout << "BrickInspector::update()" << std::endl;
		}

		// override
		void BrickInspector::renderDebug()
		{

		}
	}
}