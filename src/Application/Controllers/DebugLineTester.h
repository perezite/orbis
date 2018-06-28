#pragma once

#include "../../Orbis/Components/Component.h"
using namespace orb::components;

namespace controllers
{
	class DebugLineTester : public Component
	{
	public:
		void renderDebug();
	};
}