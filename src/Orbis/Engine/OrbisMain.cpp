#include "OrbisMain.h"

#include "../Core/TimeManager.h"
#include "../Game/LevelManager.h"
#include "../Input/InputManager.h"
#include "../Core/PerformanceLogger.h"

namespace orb
{
	OrbisMain* OrbisMain::instance()
	{
		static OrbisMain instance;
		return &instance;
	}

	void OrbisMain::run()
	{
		LevelManager* level = LevelManager::instance();
		InputManager* input = InputManager::instance();
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