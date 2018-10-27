#pragma once

#include "Color.h"
#include "RenderMode.h"

#include "../Libraries/GL.h"

#include "../../Base/Base.h"
using namespace base;

#include <vector>

namespace orb
{
	class DebugRenderDevice
	{
	public:
		// draw a debug line (slow!)
		void drawDebugLine(Vector2f start, Vector2f end, Color color);

		// draw a debug rect (slow!)
		void drawDebugRect(Rect rect, Color color);

	protected:
		// draw a debug primitve
		void drawDebugPrimitive(GLfloat* vertexArray, unsigned int vertexArrayCount, Color color, RenderMode renderMode);
	};
}