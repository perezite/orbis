#include "VertexHelper.h"

#include <assert.h>

namespace Helpers
{
	float* VertexHelper::GetVertexArray(std::vector<Vector2D> positions, std::vector<Color> colors)
	{
		assert(positions.size() == colors.size());

		float* vertexArray = new float[positions.size() * 7];

		for (int i = 0; i < positions.size(); i++)
		{
			vertexArray[i * 7 + 0] = positions[i].GetX();
			vertexArray[i * 7 + 1] = positions[i].GetY();
			vertexArray[i * 7 + 2] = 0.0f;
			vertexArray[i * 7 + 3] = colors[i].GetRed();
			vertexArray[i * 7 + 4] = colors[i].GetGreen();
			vertexArray[i * 7 + 5] = colors[i].GetBlue();
			vertexArray[i * 7 + 6] = colors[i].GetAlpha();
		}

		return vertexArray;
	}

}