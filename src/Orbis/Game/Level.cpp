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
		MemoryManager<Texture>::GetInstance()->DeleteAll();
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
			VideoManager::GetInstance()->GetRenderDevice()->ClearRenderables();
			Start();
			StartEntities();
			VideoManager::GetInstance()->GetTextureAtlas()->Generate();
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

	bool Level::HasTexture(std::string assetPath)
	{
		std::vector<Texture*> textures = MemoryManager<Texture>::GetInstance()->GetAll();
		for (unsigned int i = 0; i < textures.size(); i++)
		{
			if (textures[i]->GetAssetPath() == assetPath)
				return true;
		}

		return false;
	}

	Texture* Level::GetTexture(std::string assetPath)
	{
		std::vector<Texture*> textures = MemoryManager<Texture>::GetInstance()->GetAll();
		for (unsigned int i = 0; i < textures.size(); i++)
		{
			if (textures[i]->GetAssetPath() == assetPath)
				return textures[i];
		}

		throw Exception("The given texture does not exist");
	}

}


