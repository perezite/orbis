#pragma once

#include "Color.h"
#include "RenderMode.h"

#include "../Libraries/GL.h"

#include "../../Base/Math/Vector2D.h"
#include "../../Base/Math/Rect.h"
using namespace base::math;

#include <vector>

namespace orb
{
	namespace video
	{
		class DebugRenderDevice
		{
		public:
			// draw a debug line (slow!)
			void drawDebugLine(Vector2D start, Vector2D end, Color color);

			// draw a debug rect (slow!)
			void drawDebugRect(Rect rect, Color color);

		protected:
			// draw a debug primitve
			void drawDebugPrimitive(GLfloat* vertexArray, unsigned int vertexArrayCount, Color color, RenderMode renderMode);
		};
	}
}