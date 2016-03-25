#pragma once

#include "VideoManager.h"

#include "..\Core\Entity.h"
#include "..\Core\Component.h"
using namespace Core;

namespace Video
{
	class Renderer : public Component
	{
	public:
		// constructor
		Renderer(Entity* entity) : Component(entity) { }

		// update
		void Update();

		// render
		void Render();
	};
}