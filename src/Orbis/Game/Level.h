#pragma once

#include "LevelBuilder.h"

#include "../Game/Entity.h"

#include <vector>
#include <string>

namespace orb
{
	class LevelBuilder;

	// Represents a level in the game
	class Level
	{
	public:
		// ctor
		Level();

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

		// get the level builder
		LevelBuilder* build() { return m_levelBuilder; }

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

		// the level builder 
		LevelBuilder* m_levelBuilder;
	};
}