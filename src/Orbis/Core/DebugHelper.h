#pragma once

#include "../Video/Color.h"
using namespace video;

#include "../../Base/Math/Vector2D.h"
#include "../../Base/Math/Rect.h"
using namespace base::math;

#ifdef _DEBUG
	#define ORBIS_DEBUG(call) {call}
	#define ORBIS_RELEASE(call)
#else
	#define ORBIS_DEBUG(call)
	#define ORBIS_RELEASE(call) {call}
#endif

namespace orbis
{
	namespace core
	{
		class DebugHelper
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
}