#pragma once

#include "../../Base/Math/Math.h"
#include "../../Orbis/Components/Component.h"
using namespace orb::components;
using namespace base::math;

namespace controllers
{
	class CameraBehavior : public Component 
	{
	public:
		// get omega
		float getOmega() { return Math::getPi() / 4.0f; };
	};
}