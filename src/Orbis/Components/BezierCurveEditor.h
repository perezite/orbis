#pragma once

#include "../../Base/Math/Vector2D.h"
using namespace Math;

#include "../../Orbis/Components/Component.h"
using namespace Components;

#include <vector>

namespace Components
{
	// can be used to visualize, edit and ultimately dump the data from a bezier curve
	class BezierCurveEditor : public Component
	{
	public:
		// ctor
		BezierCurveEditor()
			: Component::Component(), m_selectedControlPoint(-1)
		{}

		// update
		void Update();

		// render
		void Render();

	protected:
		// add or select a control point at the tapped point 
		void AddOrSelectControlPoint();

		// move the selected control point to the tapped point
		void MoveControlPoint();

		// rotate the tangent to the slope defined by the right tapped point
		void RotateTangent();

		// delete the selected control point
		void DeleteSelectedControlPoint();

		// get the index of the selected control point or -1 if no point was selected
		unsigned int GetSelectedControlPoint(Vector2D tapPosition);

		// check whether a control point is selected by the given tap position
		bool IsControlPointSelected(unsigned int controlPointIndex, Vector2D tapPosition);

		// control points sorter
		static bool CompareControlPoints(Vector2D first, Vector2D second) { return first.x < second.x; };

		// render the bezier curve
		void RenderBezierCurve();

		// render the control points and tangent
		void RenderControlPoints();

		// get the bezier curve value at a parameter t
		Vector2D Bezier(float t);

		// get the bezier curve segment value at a parameter t with control points p0, p1, p2, p3
		Vector2D Bezier(float t, Vector2D p0, Vector2D p1, Vector2D p2, Vector2D p3);

	private:
		// the control points
		std::vector<Vector2D> m_controlPoints;

		// the tangents given as slopes
		std::vector<float> m_tangents;

		// the index of the selected control point
		unsigned int m_selectedControlPoint;

	private:
		// the extent of a marking rectangle for a control point
		static const float MARK_EXTENT;

		// the radius of the selection disk around a control point
		static const float SELECT_RADIUS;

		// the lenght of the tangent line segment
		static const float TANGENT_LENGTH;

		// curve sampling density (number of samples per unit line segment)
		static const int SAMPLING_DENSITY;

		// number of sampling points per curve segment
		static const int NUM_SAMPLES;
	};
}