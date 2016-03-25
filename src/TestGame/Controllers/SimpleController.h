#pragma once

#include "..\..\Orbis\Game\Component.h"
using namespace Game;

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