#include "BezierCurve.h"

#include <algorithm>

namespace Math
{
	const float BezierCurve::TANGENT_LENGTH = 0.18f;

	BezierCurve::BezierCurve(std::vector<std::pair<float, std::pair<float, float>>> controlPoints)
	{
		m_points.clear();
		for (unsigned int i = 0; i < controlPoints.size(); i++)
		{
			Vector2D pos(controlPoints[i].second.first, controlPoints[i].second.second);
			float tangent = controlPoints[i].first;
			m_points.push_back(BezierPoint(pos, tangent));
		}
	}

	Vector2D BezierCurve::GetValue(float t)
	{
		t = float(m_points.size() - 1) * t;	// map [0, 1] onto [0, (#points -1)]
		int startIdx = (int)t;
		t = t - (int)t;
		Vector2D startTangent = Vector2D(1, m_points[startIdx].tangent).Scaled(TANGENT_LENGTH);
		Vector2D endTangent = Vector2D(1, m_points[startIdx + 1].tangent).Scaled(TANGENT_LENGTH);
		Vector2D p0 = m_points[startIdx].pos;
		Vector2D p1 = p0 + startTangent * 0.5f;
		Vector2D p3 = m_points[startIdx + 1].pos;
		Vector2D p2 = p3 - endTangent * 0.5f;
		return GetValue(t, p0, p1, p2, p3);
	}

	void BezierCurve::Add(BezierPoint bp)
	{
		m_points.push_back(BezierPoint(bp.pos, bp.tangent));
		std::sort(m_points.begin(), m_points.end(), CompareControlPoints);
	}

	void BezierCurve::Move(unsigned int index, Vector2D newPosition)
	{
		std::vector<BezierPoint> newControlPoints = m_points;
		newControlPoints[index].pos = newPosition;

		// only update if the translation did not change the order of the control points
		if (std::is_sorted(std::begin(newControlPoints), std::end(newControlPoints), CompareControlPoints))
			m_points = newControlPoints;
	}

	// reference: https://www.youtube.com/watch?v=Qu-QK3uoMdY
	Vector2D BezierCurve::GetValue(float t, Vector2D p0, Vector2D p1, Vector2D p2, Vector2D p3)
	{
		float tt = t * t;
		float ttt = tt * t;
		float ti = (1 - t);
		float titi = ti * ti;
		float tititi = titi * ti;
		float x = tititi * p0.x + 3 * titi * t * p1.x + 3 * ti * tt * p2.x + ttt * p3.x;
		float y = tititi * p0.y + 3 * titi * t * p1.y + 3 * ti * tt * p2.y + ttt * p3.y;
		return Vector2D(x, y);
	}
}