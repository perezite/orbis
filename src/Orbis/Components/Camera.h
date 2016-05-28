#pragma once

#include "Component.h"

#include "..\Game\Entity.h"
using namespace Game;

namespace Components
{
	// The camera
	class Camera : public Component
	{
	public:
		// update
		void Update();

		// render
		void Render() { };
	};
}