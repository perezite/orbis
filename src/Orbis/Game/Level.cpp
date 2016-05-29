#include "Level.h"

#include "..\Video\VideoManager.h"
using namespace Video;

namespace Game
{
	Level::Level() : m_isStarted(false)
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
		if (m_isStarted == false)
		{
			StartEntities();
			m_isStarted = true;
		}
		else
		{
			UpdateEntities();

			RenderEntities();
		}
	}

	void Level::StartEntities()
	{
		for each (Entity *entity in m_entities)
		{
			entity->Start();
		}
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


