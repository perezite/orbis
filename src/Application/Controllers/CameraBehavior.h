#pragma once

#include "../../Base/Math/MathUtil.h"
#include "../../Orbis/Components/Component.h"
using namespace orb::components;
using namespace base::math;

namespace app
{
	class CameraBehavior : public Component 
	{
	public:
		// get omega
		float getOmega() { return MathUtil::getPi() / 4.0f; };
	};
}