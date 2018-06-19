#pragma once

#include "../Input/InputManager.h"
#include "../Components/Component.h"
#include "../Game/Entity.h"
#include "../Game/Level.h"
#include "../Effects/Tween.h"
#include "../Video/Renderable.h"
using namespace Input;
using namespace Components;
using namespace Game;
using namespace Effects;
using namespace Video;

#include <vector>

namespace Components
{
	// used to edit a tween
	class TweenInspector : Component
	{
	public:
		// utility for quickly creating an inspector entity. Returns 0 in release mode
		static Entity* tryConstructEntity(Level* parentLevel, Tween* tween, KeyCode activationkey = KeyCode::t);

	public:
		// ctor
		TweenInspector(Level* parentLevel, Tween* tween, KeyCode activationKey = KeyCode::t);

		// start
		void start();

		// update
		void update();

		// render
		void renderDebug();

	protected:
		// add or select a control point at the tapped position 
		void addOrSelectControlPoint();

		// move control point to the tap position
		void moveControlPoint();

		// rotate the tangent to the slope defined by the right tapped point
		void rotateTangent();

		// delete the selected control point
		void deleteSelectedControlPoint();

		// get the index of the selected control point or -1 if no point was selected
		unsigned int computeSelectedControlPoint(Vector2D tapPosition);

		// check whether a control point is selected by the given tap position
		bool isControlPointSelected(unsigned int controlPointIndex, Vector2D tapPosition);

		// render the bezier curve
		void renderCurve();

		// render the control points and tangent
		void renderControlPoints();

		// check if given points is within the clickable rect
		bool IsClickablePosition(Vector2D position);

		// is the selected control point the first or last point 
		bool IsSelectedControlPointOnBoundary();

		// shift a curve by the given vector
		void ShiftCurve(BezierCurve* curve, Vector2D shift);

		// get a curve shifted by the given vector
		BezierCurve GetShiftedCurve(BezierCurve* curve, Vector2D shift);

		// save the tween
		void save();

		// toggle the editor
		void toggle();

	private:
		// the renderable
		Renderable m_renderable;

		// the tween to be edited
		Tween m_tween;

		// the index of the selected control point
		unsigned int m_selectedControlPoint;

		// is the editor currently active
		bool m_isActive;

		// the key for activating the inspector
		KeyCode m_activationKey;

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