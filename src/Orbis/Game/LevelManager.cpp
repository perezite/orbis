#include "LevelManager.h"

#include "../Core/TimeManager.h"

#include "../../Base/Base.h"
using namespace base;

#include <iostream>

namespace orb
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
		if (m_currentLevel)
			delete m_currentLevel;
		if (m_queuedLevel)
			delete m_queuedLevel;
	}

	void LevelManager::update()
	{
		if (m_queuedLevel != NULL)
			switchToQueuedLevel();

		m_currentLevel->updateLevel();
	}

	void LevelManager::render()
	{
		m_currentLevel->render();
	}

	void LevelManager::switchToQueuedLevel()
	{
		if (m_currentLevel)
			delete m_currentLevel;
		m_currentLevel = m_queuedLevel;
		m_queuedLevel = NULL;
		m_currentLevel->startLevel();
	}
}