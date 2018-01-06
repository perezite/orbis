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

		// omega of the user tangent rotation
		static const float TANGENT_OMEGA;

	};
}