#pragma once

#include "../Video/Color.h"
using namespace orb;

#include "../../Base/Base.h"
using namespace base;

#ifdef _DEBUG
	#define ORBIS_DEBUG(call) {call}
	#define ORBIS_RELEASE(call)
#else
	#define ORBIS_DEBUG(call)
	#define ORBIS_RELEASE(call) {call}
#endif

namespace orb
{
	class DebugUtil
	{
	public:
		// draw a debug line
		static void drawLine(Vector2D start, Vector2D end, Color color = Color::Green);

		// darw a debug wireframe rectangle
		static void drawRect(Rect rect, Color color);

		// draw a debug solid rectangle
		static void drawSolidRect(Rect rect, Color color);
	};
}