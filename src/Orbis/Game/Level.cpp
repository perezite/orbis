#include "Level.h"

#include "../Video/VideoManager.h"
#include "../Effects/EffectsManager.h"
#include "../Core/TimeManager.h"
using namespace Video;
using namespace Effects;
using namespace Core;

#include "../../Base/System/MemoryHelper.h"
#include "../../Base/System/Exception.h"
using namespace System;

#include <iostream>

namespace Game
{
	Level::~Level()
	{
		EffectsManager::getInstance()->clear();
		VideoManager::getInstance()->clear();
		MemoryHelper::clear(m_entities);
	}

	void Level::Initialize()
	{
		TimeManager::getInstance()->Reset();
		VideoManager::getInstance()->clear();
		start();
		StartEntities();
		VideoManager::getInstance()->start();
	}

	void Level::Update()
	{
		TimeManager::getInstance()->Update();
		UpdateEntities();
	}

	void Level::render()
	{
		VideoManager::getInstance()->getWindow()->clear();
		RenderEntities();
	}

	void Level::StartEntities()
	{
		for(unsigned int i = 0; i < m_entities.size(); i++)
		{
			m_entities[i]->start();
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
		VideoManager* video = VideoManager::getInstance();

		video->getWindow()->clear();
		video->render();

		for (unsigned int i = 0; i < m_entities.size(); i++)
			m_entities[i]->RenderDebug();

		video->getWindow()->swapBuffers();
	}
}


