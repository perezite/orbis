#pragma once

#include "../Game/Entity.h"
using namespace Game;

#include <vector>
#include <string>

namespace Video
{
	class Texture;
}

using namespace Video;

namespace Game
{
	// Represents a level in the game
	class Level
	{
	public:
		// destructor
		virtual ~Level();

		// initialize the level
		void initialize();

		// add entity
		void addEntity(Entity *entity) { if (entity) m_entities.push_back(entity); }

		// update 
		void update();

		// render
		void render();

		// start
		virtual void start() { }

	protected:
		// start the entities
		void startEntities();

		// update entities
		void updateEntities();

		// render entities
		void renderEntities();

	private:
		// entites in the level
		std::vector<Entity*> m_entities;
	};
}