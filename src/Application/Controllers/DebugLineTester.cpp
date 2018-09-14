#include "DebugLineTester.h"

#include "../../Orbis/Orbis.h"
using namespace orb::core;

namespace controllers
{
	void DebugLineTester::renderDebug()
	{
		DebugHelper::drawLine(Vector2D(-0.2f, -0.3f), Vector2D(0.2f, 0.4f));
		DebugHelper::drawLine(Vector2D(-0.2f, 0.3f), Vector2D(0.3f, 0.3f));
	}
}
