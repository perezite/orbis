#pragma once

#include "../../Base/System/MemoryManager.h"
#include "../../Base/Math/BezierCurve.h"
using namespace System;
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
			MemoryManager<Tween>::GetInstance()->Add(this);
		}

		// get the curve
		BezierCurve* GetCurve() { return &m_curve; }

		// set the curve
		void SetCurve(BezierCurve curve) { m_curve = curve; }

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