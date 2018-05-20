#include "Level.h"

#include "../Video/VideoManager.h"
#include "../Effects/Tween.h"
using namespace Video;
using namespace Effects;

#include "../../Base/System/MemoryManager.h"
#include "../../Base/System/MemoryHelper.h"
using namespace System;

namespace Game
{
	Level::Level() : m_isStarted(false)
	{
		m_textureAtlas = new TextureAtlas();
	}

	Level::~Level()
	{
		MemoryHelper::Clear(m_entities);
		MemoryManager<Texture>::GetInstance()->DeleteAll();
		MemoryManager<Tween>::GetInstance()->DeleteAll();
	}

	void Level::AddEntity(Entity *entity)
	{
		if (entity != NULL)
			m_entities.push_back(entity);
	}

	void Level::Update()
	{
		if (m_isStarted == false) // TODO: Move this to the manager
		{
			VideoManager::GetInstance()->GetRenderDevice()->ClearRenderables();
			Start();
			StartEntities();
			m_textureAtlas->Generate();
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


