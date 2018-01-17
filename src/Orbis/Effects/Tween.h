#pragma once

#include "../../Base/Math/BezierCurve.h"
using namespace Math;

#include <string>

namespace Effects
{
	class Tween 
	{
	public:
		// ctor
		Tween(std::string assetPath) : 
			m_assetPath(assetPath) 
		{ 
			TryDeserialize();
		}

		// set the curve
		void SetCurve(BezierCurve const curve) { m_curve = curve; }

		// save as asset
		void Save();

	protected:
		// deserialize from asset if existing
		void TryDeserialize();

	private:
		// the curve
		BezierCurve m_curve;

		// the asset path
		std::string m_assetPath;
	};
}