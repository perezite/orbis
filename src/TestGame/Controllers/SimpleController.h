#pragma once

#include "..\..\Orbis\Components\Component.h"
using namespace Components;

namespace Controllers
{
	class SimpleController : public Component
	{
	public:
		// override
		void Update();

		// override
		void Render() { } 
	};
}