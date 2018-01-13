#pragma once

#include "../../Base/Math/BezierCurve.h"
using namespace Math;

#include "../../Orbis/Components/Component.h"
#include "../../Orbis/Game/Entity.h"
using namespace Components;
using namespace Game;

namespace Controllers
{
	// test the animation of an entity's scale using bezier curves 
	class BezierCurveTester : public Component
	{
	public:
		// ctor
		BezierCurveTester(BezierCurve bezierCurve, float duration) 
			: Component::Component(), m_curve(bezierCurve), m_duration(duration), m_elapsed(0.0f)
		{ }

		// override
		void Start();

		// override
		void Update();

	private: 
		// the initial scale
		Vector2D m_initialScale;

		// the bezier curve
		BezierCurve m_curve;

		// duration of the tween
		float m_duration;

		// elapsed tween time
		float m_elapsed;
	};
}