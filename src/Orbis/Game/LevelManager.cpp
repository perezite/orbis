#include "LevelManager.h"

#include "../Core/TimeManager.h"
using namespace Core;

#include "../../Base/System/Exception.h"
#include "../../Base/System/MemoryHelper.h"
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
		MemoryHelper::Delete(m_currentLevel);
		MemoryHelper::Delete(m_queuedLevel);
	}

	void LevelManager::QueueLevel(Level *level)
	{
		m_queuedLevel = level;

		if (m_currentLevel == NULL)
			SwitchToQueuedLevel();
	}

	void LevelManager::Update()
	{
		Exception::Assert(m_currentLevel != NULL, "A level must be queued before calling " + std::string(__func__));

		TimeManager::GetInstance()->Update();
		m_currentLevel->Update();

		if (m_queuedLevel != NULL)
		{
			SwitchToQueuedLevel();
		}
	}

	void LevelManager::SwitchToQueuedLevel()
	{
		MemoryHelper::Delete(m_currentLevel);
		m_currentLevel = m_queuedLevel;
		m_queuedLevel = NULL;

		TimeManager::GetInstance()->Reset();
	}
}
