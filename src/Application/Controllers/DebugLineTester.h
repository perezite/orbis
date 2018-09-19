#pragma once

#include "../../Orbis/Components/Component.h"
using namespace orb;

namespace app
{
	class DebugLineTester : public Component
	{
	public:
		void renderDebug();
	};
}