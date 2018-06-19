#include "DebugLineTester.h"

#include "../../Orbis/Core/DebugHelper.h"
using namespace Core;

namespace Controllers
{
	void DebugLineTester::renderDebug()
	{
		DebugHelper::drawLine(Vector2D(-0.2f, -0.3f), Vector2D(0.2f, 0.4f));
		DebugHelper::drawLine(Vector2D(-0.2f, 0.3f), Vector2D(0.3f, 0.3f));
	}
}
