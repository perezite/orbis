#pragma once

#include "../../Orbis/Components/Component.h"
using namespace orb::components;

namespace app
{
	class DebugLineTester : public Component
	{
	public:
		void renderDebug();
	};
}