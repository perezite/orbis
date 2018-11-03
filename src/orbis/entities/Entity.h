#pragma once

#include "../components/Component.h"

namespace orb
{
	class Entity
	{
	public:
		Entity();

		void addComponent(Component* component) { m_components.push_back(component); }

		void update();

		void render();

	private: 
		std::vector<Component*> m_components;
	};
}
