#pragma once

#include "../../Base/Math/Spline.h"
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

		// get the spline
		Spline* getSpline() { return &m_spline; }

		// set the spline
		void setSpline(Spline spline) { m_spline = spline; }

		// se the initial value
		void setInitial(Vector2D initial) { m_initial = initial; }

		// update the value
		void update(Vector2D* current, float duration);

		// save as asset
		void saveToJsonFile();

	private:
		// the spline
		Spline m_spline;

		// the asset path
		std::string m_assetPath;

		// elapsed tween time
		float m_elapsed;

		// the initial value of the tweened vector
		Vector2D m_initial;
	};
}