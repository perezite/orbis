#pragma once

#include "../../Base/Math/BezierCurve.h"
using namespace Math;

#include "../../Orbis/Components/Component.h"
#include "../../Orbis/Components/Renderer.h"
using namespace Components;

#include <vector>

namespace Components
{
	// can be used to visualize, edit and ultimately dump the data from a bezier curve
	class BezierCurveEditor : public Renderer
	{
	public:
		// ctor
		BezierCurveEditor()
			: Renderer::Renderer(), m_selectedControlPoint(-1)
		{}		

		// ctor
		BezierCurveEditor(std::vector<std::pair<float, std::pair<float, float>>> controlPoints);

		// start
		void Start();

		// update
		void Update();

		// render
		void Render();

	protected:
		// add or select a control point at the tapped point 
		void AddOrSelectControlPoint();

		// move control point to the tap position
		void MoveControlPoint();

		// rotate the tangent to the slope defined by the right tapped point
		void RotateTangent();

		// delete the selected control point
		void DeleteSelectedControlPoint();

		// copy the control point coordinates to clipboard
		void CopyControlPointsToClipboard();

		// get the index of the selected control point or -1 if no point was selected
		unsigned int ComputeSelectedControlPoint(Vector2D tapPosition);

		// check whether a control point is selected by the given tap position
		bool IsControlPointSelected(unsigned int controlPointIndex, Vector2D tapPosition);

		// render the bezier curve
		void RenderBezierCurve();

		// render the control points and tangent
		void RenderControlPoints();

		// check if given points is within the clickable rect
		bool IsClickablePosition(Vector2D position);

		// is the selected control point the first or last point 
		bool IsSelectedControlPointOnBoundary();

		// is the given point a valid point for the currently selected control point 

	private:
		// the bezier curve
		BezierCurve m_curve;

		// the index of the selected control point
		unsigned int m_selectedControlPoint;

		// the coordinate system texture
		Texture* m_texture;

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