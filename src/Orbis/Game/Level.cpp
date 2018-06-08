#include "Level.h"

#include "../Video/VideoManager.h"
#include "../Effects/EffectsManager.h"
using namespace Video;
using namespace Effects;

#include "../../Base/System/MemoryManager.h"
#include "../../Base/System/MemoryHelper.h"
#include "../../Base/System/Exception.h"
using namespace System;

namespace Game
{
	Level::Level() : m_isStarted(false)
	{}

	Level::~Level()
	{
		EffectsManager::GetInstance()->Clear();
		VideoManager::GetInstance()->Clear();
		MemoryHelper::Clear(m_entities);
	}

	void Level::AddEntity(Entity *entity)
	{
		if (entity != NULL)
			m_entities.push_back(entity);
	}

	void Level::Update()
	{
		if (m_isStarted == false) 
		{
			VideoManager::GetInstance()->Clear();
			Start();
			StartEntities();
			VideoManager::GetInstance()->Start();
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
		VideoManager* video = VideoManager::GetInstance();

		video->ClearScreen();
		video->Render();

		for (unsigned int i = 0; i < m_entities.size(); i++)
			m_entities[i]->RenderDebug();

		video->SwapBuffers();
	}
}


