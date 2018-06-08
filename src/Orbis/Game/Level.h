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
		// constructor
		Level();

		// destructor
		virtual ~Level();

		// start
		virtual void Start() { };

		// release
		virtual void Release() { };

		// add entity
		void AddEntity(Entity *entity);

		// update 
		void Update();

		// has the level a given texture
		bool HasTexture(std::string assetPath);

		// get a texture
		Texture* GetTexture(std::string assetPath);

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
		
		// is the level started
		bool m_isStarted;
	};
}