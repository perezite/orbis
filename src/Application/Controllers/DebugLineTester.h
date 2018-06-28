#pragma once

#include "../../Orbis/Components/Component.h"
using namespace orbis::components;

namespace controllers
{
	class DebugLineTester : public Component
	{
	public:
		void renderDebug();
	};
}