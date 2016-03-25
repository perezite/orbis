#pragma once

#include "..\Game\Entity.h"
using namespace Game;

#include <vector>

namespace Game
{
	// Represents a level in the game
	class Level
	{
	public:
		// constructor
		Level();

		// destructor
		virtual ~Level();

		// gets called when level is loaded
		virtual void OnLoad() { };

		// add entity
		void AddEntity(Entity *entity);

		// update 
		void Update();

	protected:
		// update entities
		void UpdateEntities();

		// render entities
		void RenderEntities();
	private:
		// entites in the level
		std::vector<Entity*> m_entities;

	};
}