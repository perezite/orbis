#include "Level.h"

#include "../Video/VideoManager.h"
#include "../Video/TextureAtlas.h"
#include "../Effects/Tween.h"
using namespace Video;
using namespace Effects;

#include "../../Base/System/MemoryManager.h"
using namespace System;

namespace Game
{
	Level::Level() : m_isStarted(false)
	{
		OnLoad();
	}

	Level::~Level()
	{
		for(unsigned int i = 0; i < m_entities.size(); i++)
		{
			delete m_entities[i];
		}

		m_entities.clear();
	
		MemoryManager<Texture>::GetInstance()->DeleteAll();
		MemoryManager<Tween>::GetInstance()->DeleteAll();
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
			TextureAtlas::GetInstance()->Generate();
			m_isStarted = true;
		}
		else
		{
			UpdateEntities();
			VideoManager::GetInstance()->ClearScreen();
			RenderEntities();
		}
	}

	void Level::StartEntities()
	{
		for(unsigned int i = 0; i < m_entities.size(); i++)
		{
			m_entities[i]->Start();
		}
	}

	void Level::UpdateEntities()
	{
		for (unsigned int i = 0; i < m_entities.size(); i++)
		{
			m_entities[i]->Update();
		}
	}

	void Level::RenderEntities()
	{
		VideoManager* videoManager = VideoManager::GetInstance();

		videoManager->ClearScreen();

		videoManager->GetRenderDevice()->Render();

		for (unsigned int i = 0; i < m_entities.size(); i++)
		{
			m_entities[i]->Render();
		}

		videoManager->SwapBuffers();
	}

}


