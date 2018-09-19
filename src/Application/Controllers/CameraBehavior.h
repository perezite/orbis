#pragma once

#include "../../Base/Math/MathUtil.h"
using namespace base;

#include "../../Orbis/Components/Component.h"
using namespace orb;


namespace app
{
	class CameraBehavior : public Component 
	{
	public:
		// get omega
		float getOmega() { return MathUtil::getPi() / 4.0f; };
	};
}