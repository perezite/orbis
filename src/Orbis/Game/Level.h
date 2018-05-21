#pragma once

#include "../Game/Entity.h"
#include "../Video/TextureAtlas.h"
using namespace Game;

#include <vector>
#include <string>

namespace Video
{
	class Texture;
	class TextureAtlas;
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

		// add entity
		void AddEntity(Entity *entity);

		// update 
		void Update();

		// get the texture atlas
		Video::TextureAtlas* GetTextureAtlas() { return m_textureAtlas; }

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

		// the texture atlas
		TextureAtlas* m_textureAtlas;
	};
}