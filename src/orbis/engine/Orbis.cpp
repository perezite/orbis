#include "Orbis.h"
#include "../video/VideoManager.h"

namespace orb
{
	Orbis* Orbis::instance()
	{
		static Orbis instance;
		return &instance;
	}

	void Orbis::queueLevel(void(*level)(void))
	{
		m_isLevelRunning = false; 
		m_queuedLevel = level; 
	}

	void Orbis::runLevel() 
	{ 
		m_isLevelRunning = true; 
		m_queuedLevel(); 
		m_queuedLevel = NULL;
	}

	void Orbis::updateFrame()
	{
		m_currentLevel->update();
		m_currentLevel->render();
		VideoManager::instance()->getRenderDevice()->render();
	}

	Orbis::Orbis() : m_isLevelRunning(true), m_queuedLevel(NULL)
	{
		m_currentLevel = new Level();
	}
}

