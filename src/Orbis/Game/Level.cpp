#include "Level.h"

#include "..\Video\VideoManager.h"
using namespace Video;

namespace Game
{
	Level::Level()
	{
		OnLoad();
	}

	Level::~Level()
	{
		for each (Entity *entity in m_entities)
		{
			delete entity;
		}

		m_entities.clear();
	}

	void Level::AddEntity(Entity *entity)
	{
		m_entities.push_back(entity);
	}

	void Level::Update()
	{
		UpdateEntities();

		RenderEntities();
	}

	void Level::UpdateEntities()
	{
		for each (Entity *entity in m_entities)
		{
			entity->Update();
		}
	}

	void Level::RenderEntities()
	{
		VideoManager* videoManager = VideoManager::GetInstance();

		videoManager->ClearScreen();

		for each (Entity *entity in m_entities)
		{
	
			entity->Render();
		}

		videoManager->SwapBuffers();
	}

}


