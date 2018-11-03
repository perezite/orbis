#pragma once

#include "../entities/Entity.h"

#include <vector>

namespace orb
{
	class Level
	{
	public:
		Level() {}

		void addEntity(Entity* entity) { m_entities.push_back(entity); }

		void update();

		void render();

	private: 
		std::vector<Entity*> m_entities;
	};
}
