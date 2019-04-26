#include "DebugLineTester.h"

#include "../../Orbis/Orbis.h"
using namespace orb;

namespace app
{
	void DebugLineTester::renderDebug()
	{
		DebugUtil::drawLine(Vector2f(-0.2f, -0.3f), Vector2f(0.2f, 0.4f));
		DebugUtil::drawLine(Vector2f(-0.2f, 0.3f), Vector2f(0.3f, 0.3f));
	}
}
