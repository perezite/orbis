#pragma once

#include <vector>

namespace Math
{
	class BezierCurve
	{
	private: 
		// the control points
		std::vector<Vector2D> m_controlPoints;

		// the tangents given as slopes
		std::vector<float> m_tangents;
	};
}