#pragma once

#include "..\..\Orbis\Components\Component.h"
using namespace Components;

#include "..\..\Orbis\Math\Vector2D.h"
using namespace Math;

namespace Controllers
{
	class CameraController : public Component
	{
	public:
		// override
		void Update();

		// override
		void Start();

	private:
		// is the camera heading left
		bool m_isHeadingLeft;

		// is the camera scaling down
		bool m_isScalingDown;

		// initial horizontal scale
		Vector2D m_initialScale;
	};
}