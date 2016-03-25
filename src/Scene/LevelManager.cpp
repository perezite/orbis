#include "LevelManager.h"

namespace Scene
{
	LevelManager::LevelManager() :
		m_currentLevel(NULL),
		m_queuedLevel(NULL)
	{

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
	}

	void LevelManager::Update()
	{
		if (m_currentLevel != NULL)
		{
			m_currentLevel->Update();
			m_currentLevel->Render();
		}

		if (m_queuedLevel != NULL)
		{
			ApplyQueuedLevel();
		}
	}
	void LevelManager::ApplyQueuedLevel()
	{
		if (m_currentLevel != NULL)
			delete m_currentLevel;

		m_currentLevel = m_queuedLevel;
		m_queuedLevel = NULL;
	}
}