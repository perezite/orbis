#include "Level.h"

#include "../Video/VideoManager.h"
#include "../Effects/EffectsManager.h"
#include "../Core/TimeManager.h"
using namespace Video;
using namespace Effects;
using namespace Core;

#include "../../Base/System/MemoryManager.h"
#include "../../Base/System/MemoryHelper.h"
#include "../../Base/System/Exception.h"
using namespace System;

#include <iostream>

namespace Game
{
	Level::~Level()
	{
		EffectsManager::GetInstance()->Clear();
		VideoManager::GetInstance()->Clear();
		MemoryHelper::Clear(m_entities);
	}

	void Level::Initialize()
	{
		TimeManager::GetInstance()->Reset();
		VideoManager::GetInstance()->Clear();
		Start();
		StartEntities();
		VideoManager::GetInstance()->Start();
	}

	void Level::Update()
	{
		TimeManager::GetInstance()->Update();
		UpdateEntities();
		VideoManager::GetInstance()->ClearScreen();
		RenderEntities();
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


