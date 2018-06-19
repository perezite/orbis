#include "LevelManager.h"

#include "../Core/TimeManager.h"
using namespace Core;

#include "../../Base/System/Exception.h"
using namespace System;

#include <iostream>

namespace Game
{
	LevelManager::LevelManager() :
		m_currentLevel(NULL), m_queuedLevel(NULL)
	{ }

	LevelManager * LevelManager::getInstance()
	{
		static LevelManager instance;
		return &instance;
	}
	
	void LevelManager::clear()
	{
		if(m_currentLevel)
			delete m_currentLevel;
		if (m_queuedLevel)
			delete m_queuedLevel;
	}

	void LevelManager::Update()
	{
		if (m_queuedLevel != NULL)
			SwitchToQueuedLevel();

		m_currentLevel->Update();
	}

	void LevelManager::render()
	{
		m_currentLevel->render();
	}

	void LevelManager::SwitchToQueuedLevel()
	{
		if (m_currentLevel)
			delete m_currentLevel;
		m_currentLevel = m_queuedLevel;
		m_queuedLevel = NULL;
		m_currentLevel->Initialize();
	}
}
