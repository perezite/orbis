#include "BinPackingVisualizer.h"

#include "../../Orbis/Core/DebugHelper.h"
using namespace Core;

namespace Controllers
{
	BinPackingVisualizer::BinPackingVisualizer()
	{
	}

	void BinPackingVisualizer::Render()
	{
		// DebugHelper::DrawLine(Vector2D(-0.25f, -0.25f), Vector2D(0.25f, 0.25f));
		DebugHelper::DrawRect(Rect(-0.25f, -0.25f, 0.25f, 0.25f), Color::Green);
	}
}
