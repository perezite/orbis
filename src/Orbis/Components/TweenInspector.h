#pragma once

#include "../../Orbis/Components/Component.h"
#include "../../Orbis/Components/Renderer.h"
#include "../../Orbis/Game/Entity.h"
#include "../../Orbis/Effects/Tween.h"
using namespace Components;
using namespace Game;
using namespace Effects;

#include <vector>

namespace Components
{
	// used to edit a tween
	class TweenInspector : public Renderer
	{
	public:
		// utility for quickly creating an inspector entity. Returns 0 in release mode
		static Entity* TryConstructEntity(Tween* tween);

	public:
		// ctor
		TweenInspector(Tween* tween)
			: Renderer::Renderer(), m_tween(*tween)
		{
			ShiftCurve(m_tween.GetCurve(), Vector2D(-0.5f, -0.5f));
		}

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

		// get the index of the selected control point or -1 if no point was selected
		unsigned int ComputeSelectedControlPoint(Vector2D tapPosition);

		// check whether a control point is selected by the given tap position
		bool IsControlPointSelected(unsigned int controlPointIndex, Vector2D tapPosition);

		// render the bezier curve
		void RenderCurve();

		// render the control points and tangent
		void RenderControlPoints();

		// check if given points is within the clickable rect
		bool IsClickablePosition(Vector2D position);

		// is the selected control point the first or last point 
		bool IsSelectedControlPointOnBoundary();

		// shift a curve by the given vector
		void ShiftCurve(BezierCurve* curve, Vector2D shift);

		// get a curve shifted by the given vector
		BezierCurve GetShiftedCurve(BezierCurve* curve, Vector2D shift);

		// save the tween
		void Save();
	private:
		// the tween to be edited
		Tween m_tween;

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