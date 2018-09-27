#pragma once

#include "../Game/Entity.h"

#include <vector>
#include <string>

namespace orb
{
	class Texture;

	// Represents a level in the game
	class Level
	{
	public:
		// destructor
		virtual ~Level();

		// start the level
		void startLevel();

		// get entity 
		Entity* findEntity(std::string name);

		// add entity
		void addEntity(Entity *entity);

		// update the level 
		void updateLevel();

		// render
		void render();

		// start
		virtual void start() { }

		// update
		virtual void update() { } 

	protected:
		// start the entities
		void startEntities();

		// updateLevel entities
		void updateEntities();

		// render entities
		void renderEntities();

	private:
		// entites in the level
		std::vector<Entity*> m_entities;
	};
}