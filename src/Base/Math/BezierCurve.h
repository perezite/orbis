#pragma once

#include "../../Base/Math/Vector2D.h"
using namespace Math;

#include <vector>
#include <sstream>

namespace Math
{
	struct BezierPoint 
	{
	public:
		// ctor
		BezierPoint(Vector2D pos_, float tangent_)
			: pos(pos_), tangent(tangent_)
		{}

	public:
		// the position
		Vector2D pos;

		// the tangent of the point
		float tangent;
	};

	class BezierCurve
	{
	public:
		// ctor
		BezierCurve();

		// ctor
		BezierCurve(std::vector<std::pair<float, std::pair<float, float>>> controlPoints);

		// ctor 
		BezierCurve(std::vector<BezierPoint> points) : m_points(points)
		{ }

		// get the bezier curve value at coordinate x
		Vector2D GetValue(float x);

		// get a control point
		BezierPoint Get(unsigned int index) const { return m_points[index]; }

		// get the number of control points
		unsigned int GetLength() const { return m_points.size(); }

		// set a control point
		void Set(unsigned int index, BezierPoint p) { m_points[index] = p; }

		// delete a control point
		void Delete(unsigned int index) { m_points.erase(m_points.begin() + index); }

		// add a control point
		void Add(BezierPoint bp);

		// move a control point
		void Move(unsigned int index, Vector2D newPosition);

		// load from json
		void Load(std::string json);

		// serialize to json
		std::string ToString();
	protected:
		// get the bezier curve segment value at a parameter t with control points p0, p1, p2, p3
		Vector2D GetValue(float t, Vector2D p0, Vector2D p1, Vector2D p2, Vector2D p3);

		// control points sorting function
		static bool CompareControlPoints(BezierPoint first, BezierPoint second) { return first.pos.x < second.pos.x; };

		// reset the control points
		void Reset();

	private: 
		// the control points
		std::vector<BezierPoint> m_points;

		// the length of a tangent
		static const float TANGENT_LENGTH;
	};
}