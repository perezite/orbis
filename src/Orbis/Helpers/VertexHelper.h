#pragma once

#include "../../Base/Math/Vector2D.h"
using namespace Math;

#include "../Video/Color.h"
using namespace Video;

#include <vector>

namespace Helpers
{
	class VertexHelper 
	{
	public:
		// convert a vector of vertices to a vertex array
		static float* GetVertexArray(std::vector<Vector2D> positions, std::vector<Color> colors);
	};
}