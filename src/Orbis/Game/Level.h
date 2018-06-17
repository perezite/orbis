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
		void Initialize();

		// add entity
		void AddEntity(Entity *entity) { if (entity) m_entities.push_back(entity); }

		// update 
		void Update();

		// render
		void Render();

		// start
		virtual void Start() { }

	protected:
		// start the entities
		void StartEntities();

		// update entities
		void UpdateEntities();

		// render entities
		void RenderEntities();

	private:
		// entites in the level
		std::vector<Entity*> m_entities;
	};
}