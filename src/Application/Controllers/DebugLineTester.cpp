#include "DebugLineTester.h"

#include "../../Orbis/Core/DebugHelper.h"
using namespace Core;

namespace Controllers
{
	void DebugLineTester::Render()
	{
		DebugHelper::DrawLine(Vector2D(-0.2f, -0.3f), Vector2D(0.2f, 0.4f));
		DebugHelper::DrawLine(Vector2D(-0.2f, 0.3f), Vector2D(0.3f, 0.3f));
	}
}
