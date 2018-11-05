#include "Orbis.h"
#include "../video/VideoManager.h"

namespace orb
{
	Orbis* Orbis::instance()
	{
		static Orbis instance;
		return &instance;
	}

	void Orbis::updateFrame()
	{
		m_currentLevel->update();
		m_currentLevel->render();
		VideoManager::instance()->getRenderDevice()->render();
	}

	Orbis::Orbis() : m_isRunning(true)
	{
		m_currentLevel = new Level();
	}
}

