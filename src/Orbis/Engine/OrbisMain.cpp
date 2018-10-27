#include "OrbisMain.h"

#include "../Core/TimeManager.h"
#include "../Game/LevelManager.h"
#include "../Input/InputManager.h"
#include "../Core/PerformanceLogger.h"

namespace orb
{
	OrbisMain* OrbisMain::getInstance()
	{
		static OrbisMain instance;
		return &instance;
	}

	void OrbisMain::run()
	{
		LevelManager* level = LevelManager::getInstance();
		InputManager* input = InputManager::getInstance();
		TimeManager* time = TimeManager::instance();
		PerformanceLogger performance;

		while (!input->hasQuitEvent())
		{
			time->update();
			input->update();
			level->update();
			level->render();

			if (m_onRenderedCallback)
				m_onRenderedCallback(); 

			performance.log();
		}

		input->clear();
		level->clear();
	}
}