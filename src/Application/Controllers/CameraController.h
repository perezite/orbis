#pragma once

#include "../../Base/Math/MathHelper.h"
#include "../../Orbis/Components/Component.h"
using namespace orb::components;
using namespace base::math;

namespace controllers
{
	class CameraController : public Component 
	{
	public:
		// get omega
		float getOmega() { return MathHelper::getPi() / 4.0f; };
	};
}