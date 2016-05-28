#pragma once

#include "..\..\Orbis\Components\Component.h"
using namespace Components;

namespace Controllers
{
	class CameraController : public Component
	{
	public:
		// ctor
		CameraController();

		// override
		void Update();

		// override
		void Render() { }

	private:
		// is the camera heading left
		bool isHeadingLeft;

		// is the camera scaling down
		bool isScalingDown;
	};
}