#pragma once

#include "../Input/InputManager.h"
#include "../Components/Component.h"
#include "../Game/Entity.h"
#include "../Game/Level.h"
#include "../Effects/Tween.h"
#include "../Video/Renderable.h"
using namespace orb::input;
using namespace orb::components;
using namespace orb::game;
using namespace orb::effects;
using namespace orb::video;

#include <vector>

namespace orb
{
	namespace components
	{
		// used to edit a tween
		class TweenInspector : public Component
		{
		public:
			// ctor
			TweenInspector(Tween* tween, KeyCode activationKey = KeyCode::t);

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

			// render the bezier spline
			void renderSpline();

			// render the control points and tangent
			void renderBezierPoints();

			// check if given points is within the clickable rect
			bool IsClickablePosition(Vector2D position);

			// is the selected control point the first or last point 
			bool IsSelectedControlPointOnBoundary();

			// shift a spline bys the given vector
			void ShiftSpline(Spline* spline, Vector2D shift);

			// get a spline shifted by the given vector
			Spline GetShiftedSpline(Spline* spline, Vector2D shift);

			// save the tween
			void saveToJsonFile();

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

			// spline sampling density (number of samples per unit line segment)
			static const int SAMPLING_DENSITY;

			// number of sampling points per spline segment
			static const int NUM_SAMPLES;
		};
	}
}