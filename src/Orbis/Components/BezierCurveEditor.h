#pragma once

#include "../../Base/Math/BezierCurve.h"
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

		// rotate the tangent to the slope defined by the right tapped point
		void RotateTangent();

		// delete the selected control point
		void DeleteSelectedControlPoint();

		// get the index of the selected control point or -1 if no point was selected
		unsigned int ComputeSelectedControlPoint(Vector2D tapPosition);

		// check whether a control point is selected by the given tap position
		bool IsControlPointSelected(unsigned int controlPointIndex, Vector2D tapPosition);

		// render the bezier curve
		void RenderBezierCurve();

		// render the control points and tangent
		void RenderControlPoints();

	private:
		// the bezier curve
		BezierCurve m_curve;

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