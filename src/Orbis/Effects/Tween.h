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
		Tween(std::string assetPath) :
			m_assetPath(assetPath), m_elapsed(0.0f)
		{
			TryDeserialize();
		}

		// get the curve
		BezierCurve* GetCurve() { return &m_curve; }

		// set the curve
		void SetCurve(BezierCurve curve) { m_curve = curve; }

		// se the initial value
		void SetInitial(Vector2D initial) { m_initial = initial; }

		// save as asset
		void Save();

		// update the value
		void Update(Vector2D* current, float duration);

	protected:
		// deserialize from asset if existing
		void TryDeserialize();

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