#pragma once

#include "../../Base/Math/MathHelper.h"
#include "../../Orbis/Components/Component.h"
using namespace Components;
using namespace Math;

namespace Controllers
{
	class CameraController : public Component 
	{
	public:
		// get omega
		float getOmega() { return MathHelper::getPi() / 4.0f; };
	};
}