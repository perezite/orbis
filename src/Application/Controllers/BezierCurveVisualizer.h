#pragma once

#include "../../Base/Math/Vector2D.h"
using namespace Math;

#include "../../Orbis/Components/Component.h"
using namespace Components;

#include <vector>

namespace Controllers
{
	// visualizes a bezier curve
	class BezierCurveVisualizer : public Component
	{
	public:
		// ctor
		BezierCurveVisualizer()
			: Component::Component(), m_selectedControlPoint(-1)
		{}

		// update
		void Update();

		// render
		void Render();

	protected:
		// get the index of the selected control point or -1 if no point was selected
		unsigned int GetSelectedControlPoint(Vector2D tapPosition);

		// check whether a control point is selected by the given tap position
		bool IsControlPointSelected(unsigned int controlPointIndex, Vector2D tapPosition);

		// control points sorter
		static bool CompareControlPoints(Vector2D first, Vector2D second) { return first.x < second.x; };

		// render a bezier line segment
		void RenderBezierSegment(unsigned int endIndex);

		// get the bezier curve value at parameter t with control points p0, p1
		Vector2D Bezier(float t, Vector2D p0, Vector2D p1);

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

	};
}