#include "Inspector.h"

namespace orb
{
	namespace inspectors
	{
		class BrickInspector : Inspector
		{	
			// override
			void start();

			// override
			void update();

			// override
			void renderDebug();
		};
	}
}