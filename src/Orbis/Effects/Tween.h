#pragma once

#include "../../Base/Math/BezierCurve.h"
using namespace Math;

#include <string>
#include <iostream>

namespace Effects
{
	// apply smooth value changes to a vector
	class Tween 
	{
	public:
		// ctor
		Tween(std::string assetPath); 

		// get the curve
		BezierCurve* getCurve() { return &m_curve; }

		// set the curve
		void setCurve(BezierCurve curve) { m_curve = curve; }

		// se the initial value
		void setInitial(Vector2D initial) { m_initial = initial; }

		// save as asset
		void saveToJsonFile();

		// update the value
		void update(Vector2D* current, float duration);

	private:
		// the curve
		BezierCurve m_curve;

		// the asset path
		std::string m_assetPath;

		// elapsed tween time
		float m_elapsed;

		// the initial value of the tweened vector
		Vector2D m_initial;
	};
}