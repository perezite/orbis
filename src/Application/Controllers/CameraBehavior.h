#pragma once

#include "../../Base/Base.h"
using namespace base;

#include "../../Orbis/Orbis.h"
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