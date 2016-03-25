#pragma once

#include "..\Core\Entity.h"
using namespace Core;

#include <vector>

namespace Scene
{
	// Represents a level in the game
	class Level
	{
	public:
		// constructor
		Level() { };

		// destructor
		virtual ~Level();

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