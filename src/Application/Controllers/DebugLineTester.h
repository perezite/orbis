#pragma once

#include "../../Orbis/Components/Component.h"
using namespace Components;

namespace Controllers
{
	class DebugLineTester : public Component
	{
	public:
		void renderDebug();
	};
}