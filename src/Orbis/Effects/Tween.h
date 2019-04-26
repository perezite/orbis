#pragma once

#include "../../Base/Base.h"
using namespace base;

#include <string>
#include <iostream>

namespace orb
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

		// updateLevel the value
		float getValue(float duration);

		// save as asset
		void saveToJsonFile();

	protected:
		// create an inspector entity for this tween
		void createInspectorEntity();

	private:
		// the spline
		Spline m_spline;

		// the asset path
		std::string m_assetPath;

		// elapsed tween time
		float m_elapsed;
	};
}