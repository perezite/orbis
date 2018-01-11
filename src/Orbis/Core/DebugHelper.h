#pragma once

#include "../Video/Color.h"
using namespace Video;

#include "../../Base/Math/Vector2D.h"
#include "../../Base/Math/Rect.h"
using namespace Math;

#ifdef _DEBUG
	#define ORBIS_DEBUG(call) {call}
	#define ORBIS_RELEASE(call)
#else
	#define ORBIS_DEBUG(call)
	#define ORBIS_RELEASE(call) {call}
#endif

namespace Core
{
	class DebugHelper
	{
	public:
		// draw a debug line
		static void DrawLine(Vector2D start, Vector2D end, Color color = Color::Green);

		// darw a debug wireframe rectangle
		static void DrawRect(Rect rect, Color color);

		// draw a debug solid rectangle
		static void DrawSolidRect(Rect rect, Color color);
	};
}