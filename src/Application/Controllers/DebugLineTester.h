#pragma once

#include "../../Orbis/Components/Component.h"
using namespace components;

namespace controllers
{
	class DebugLineTester : public Component
	{
	public:
		void renderDebug();
	};
}