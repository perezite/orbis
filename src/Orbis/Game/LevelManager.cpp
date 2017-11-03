#include "LevelManager.h"

#include "../Core/TimeManager.h"
using namespace Core;

#include "..\..\Base\System\Exception.h"
using namespace System;

#include <iostream>

namespace Game
{
	LevelManager::LevelManager() :
		m_currentLevel(NULL),
		m_queuedLevel(NULL) { }

	LevelManager * LevelManager::GetInstance()
	{
		static LevelManager instance;
		
		return &instance;
	}

	LevelManager::~LevelManager()
	{
		if (m_currentLevel != NULL)
			delete m_currentLevel;
		if (m_queuedLevel != NULL)
			delete m_queuedLevel;
	}

	void LevelManager::QueueLevel(Level *level)
	{
		m_queuedLevel = level;

		if (m_currentLevel == NULL)
			SwitchToQueuedLevel();
	}

	void LevelManager::Heartbeat()
	{
		if (m_currentLevel == NULL)
		{
			throw Exception("A level must be queued before calling " + std::string(__func__));
		}

		TimeManager::GetInstance()->Update();
		m_currentLevel->Heartbeat();

		if (m_queuedLevel != NULL)
		{
			SwitchToQueuedLevel();
		}
	}
	
	void LevelManager::SwitchToQueuedLevel()
	{
		if (m_currentLevel != NULL)
			delete m_currentLevel;

		m_currentLevel = m_queuedLevel;
		m_queuedLevel = NULL;

		TimeManager::GetInstance()->Reset();
	}
}
