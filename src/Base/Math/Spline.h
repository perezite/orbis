#pragma once

#include "../Math/Vector2.h"

#include <vector>
#include <sstream>

namespace base
{
	// a control point on a bezier spline
	struct BezierPoint
	{
	public:
		// ctor
		BezierPoint(Vector2f pos_, float tangent_)
			: pos(pos_), tangent(tangent_)
		{}

	public:
		// the position
		Vector2f pos;

		// the tangent of the point
		float tangent;
	};

	// a bezier spline
	class Spline
	{
	public:
		// ctor
		Spline();

		// ctor
		Spline(std::vector<std::pair<float, std::pair<float, float>>> controlPoints);

		// ctor 
		Spline(std::vector<BezierPoint> points) : m_points(points)
		{ }

		// get the spline value at coordinate x
		Vector2f getValue(float x);

		// get a control point
		BezierPoint get(unsigned int index) const { return m_points[index]; }

		// get the number of control points
		unsigned int getCount() const { return m_points.size(); }

		// set a control point
		void set(unsigned int index, BezierPoint p) { m_points[index] = p; }

		// delete a control point
		void remove(unsigned int index) { m_points.erase(m_points.begin() + index); }

		// add a control point
		void add(BezierPoint bp);

		// move a control point
		void move(unsigned int index, Vector2f newPosition);

		// load from json
		void loadFromJson(std::string jsonStr);

		// convert to json
		std::string toJson();
	protected:
		// get the spline segment value at a parameter t with control points p0, p1, p2, p3
		Vector2f getValue(float t, Vector2f p0, Vector2f p1, Vector2f p2, Vector2f p3);

		// control points sorting function
		static bool compareControlPoints(BezierPoint first, BezierPoint second) { return first.pos.x < second.pos.x; };

		// clear the control points
		void clear();

	private:
		// the control points
		std::vector<BezierPoint> m_points;

		// the length of a tangent
		static const float TANGENT_LENGTH;
	};
}