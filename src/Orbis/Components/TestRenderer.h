#pragma once

#include "..\Game\Entity.h"
#include "..\Game\Component.h"
using namespace Game;

namespace Video
{
	// A test renderer which renders a small box at the position of the entity
	class TestRenderer : public Component
	{
	public:
		// constructor
		TestRenderer(Entity* entity) : Component(entity) { }

		// update
		void Update();

		// render
		void Render();
	};
}