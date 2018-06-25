#include "Spline.h"

#include "../System/StringHelper.h"
#include "../Serialization/JsonReader.h"
#include "../Serialization/JsonWriter.h"
using namespace System;
using namespace Serialization;

#include <algorithm>
#include <sstream>

namespace Math
{
	const float Spline::TANGENT_LENGTH = 0.5f;

	Spline::Spline()
	{
		clear();
	}

	Vector2D Spline::getValue(float x)
	{
		unsigned int startIdx = 0;
		for (unsigned int i = 0; i < m_points.size() - 1; i++) {
			float left = m_points[i].pos.x;
			float right = m_points[i + 1].pos.x;
			if (x > left && x <= right)
				startIdx = i;
		}

		Vector2D startTangent = Vector2D(1, m_points[startIdx].tangent).scaled(TANGENT_LENGTH);
		Vector2D endTangent = Vector2D(1, m_points[startIdx + 1].tangent).scaled(TANGENT_LENGTH);
		Vector2D p0 = m_points[startIdx].pos;
		Vector2D p1 = p0 + startTangent * 0.5f;
		Vector2D p3 = m_points[startIdx + 1].pos;
		Vector2D p2 = p3 - endTangent * 0.5f;
		float t = (x - p0.x) / (p3.x - p0.x);
		return Vector2D(x, getValue(t, p0, p1, p2, p3).y);
	}

	void Spline::add(BezierPoint bp)
	{
		m_points.push_back(BezierPoint(bp.pos, bp.tangent));
		std::sort(m_points.begin(), m_points.end(), compareControlPoints);
	}

	void Spline::move(unsigned int index, Vector2D newPosition)
	{
		std::vector<BezierPoint> newControlPoints = m_points;
		newControlPoints[index].pos = newPosition;

		// only update if the translation did not change the order of the control points
		if (std::is_sorted(std::begin(newControlPoints), std::end(newControlPoints), compareControlPoints))
			m_points = newControlPoints;
	}

	void Spline::loadFromJson(std::string jsonStr)
	{
		m_points.clear();

		JsonReader reader(jsonStr);
		while (reader.getChild())
		{
			float tangent = reader.getFloat();
			reader.getChild();
			float x = reader.getFloat(); float y = reader.getFloat();
			Vector2D pos(x, y);
			m_points.push_back(BezierPoint(pos, tangent));
		}
	}

	std::string Spline::toJson()
	{
		JsonWriter writer;
		for (unsigned int i = 0; i < getCount(); i++) 
		{
			writer.beginChild();
				writer.addFloat(get(i).tangent);
				writer.beginChild();
					writer.addFloat(get(i).pos.x);
					writer.addFloat(get(i).pos.y);
				writer.endChild();
			writer.endChild();
		}

		return writer.toString();
	}

	// reference: https://www.youtube.com/watch?v=Qu-QK3uoMdY
	Vector2D Spline::getValue(float t, Vector2D p0, Vector2D p1, Vector2D p2, Vector2D p3)
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

	void Spline::clear()
	{
		m_points.clear();
		add(BezierPoint(Vector2D(0.0f, 1.0f), 0.0f));
		add(BezierPoint(Vector2D(1.0f, 1.0f), 0.0f));
	}
}