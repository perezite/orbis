#include "BezierCurve.h"

#include "../System/StringHelper.h"
using namespace System;

#include <algorithm>
#include <sstream>

namespace Math
{
	const float BezierCurve::TANGENT_LENGTH = 0.5f;// 0.18f;

	BezierCurve::BezierCurve()
	{
		Reset();
	}

	Vector2D BezierCurve::GetValue(float x)
	{
		unsigned int startIdx = 0;
		for (unsigned int i = 0; i < m_points.size() - 1; i++) {
			float left = m_points[i].pos.x;
			float right = m_points[i + 1].pos.x;
			if (x > left && x <= right)
				startIdx = i;
		}

		Vector2D startTangent = Vector2D(1, m_points[startIdx].tangent).Scaled(TANGENT_LENGTH);
		Vector2D endTangent = Vector2D(1, m_points[startIdx + 1].tangent).Scaled(TANGENT_LENGTH);
		Vector2D p0 = m_points[startIdx].pos;
		Vector2D p1 = p0 + startTangent * 0.5f;
		Vector2D p3 = m_points[startIdx + 1].pos;
		Vector2D p2 = p3 - endTangent * 0.5f;
		float t = (x - p0.x) / (p3.x - p0.x);
		return Vector2D(x, GetValue(t, p0, p1, p2, p3).y);
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

	void BezierCurve::Load(std::string json)
	{
		m_points.clear();
		std::istringstream is(json);

		StringHelper::Seek(is, '{');

		while (true)
		{
			StringHelper::Seek(is, '{');
			float tangent = (float)atof(StringHelper::Read(is, 'f').c_str());
			StringHelper::Seek(is, ','); StringHelper::Seek(is, '{');
			std::string vs = StringHelper::Read(is, '}'); vs = '{' + vs + '}';
			Vector2D pos = Vector2D::Load(vs);
			StringHelper::Seek(is, '}');
			m_points.push_back(BezierPoint(pos, tangent));

			if (!StringHelper::Seek(is, ','))
				break;
		}

		StringHelper::Seek(is, '}');
	}

	std::string BezierCurve::ToString()
	{
		std::stringstream ss;
		ss << "{";

		for (unsigned int i = 0; i < GetLength(); i++)
		{
			float tangent = Get(i).tangent;
			Vector2D pos = Get(i).pos;
			ss << "{" << StringHelper::Load(tangent) << "," << pos.Load() << "}";

			if (i < GetLength() - 1)
				ss << ",";
		}

		ss << "}";

		return ss.str();
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

	void BezierCurve::Reset()
	{
		m_points.clear();
		Add(BezierPoint(Vector2D(0.0f, 0.0f), 0.0f));
		Add(BezierPoint(Vector2D(1.0f, 1.0f), 0.0f));
	}
}