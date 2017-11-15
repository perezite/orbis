#pragma once

#include "../../Orbis/Components/Component.h"
using namespace Components;

namespace Controllers
{
	class CameraController : public Component 
	{
	public:
		void Update();
	};
}