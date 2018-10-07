#include "OrbisMain.h"

#include "../Core/TimeManager.h"
#include "../Core/LogUtil.h"
#include "../Game/LevelManager.h"
#include "../Input/InputManager.h"
#include "../Libraries/SDL.h"
#include "../Engine/Settings.h"

#include "../../Base/Base.h"
using namespace base;

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

		m_startTicks = TimeManager::getInstance()->getTicks();
		m_numFrames = 0;

		while (true)
		{
			input->update();
			if (input->hasQuitEvent())
				break;

			level->update();
			level->render();

			#if defined(ORBIS_LOG_PERFORMANCE)
				logPerformance();
			#endif
		}

		level->clear();
	}

	void OrbisMain::logPerformance()
	{
		m_numFrames++;
		if (TimeManager::getInstance()->getTicks() - m_startTicks > 1000)
		{
			// track current performance
			float currentPerformance = 1000.0f / float(m_numFrames);
			m_startTicks += 1000;
			m_numFrames = 0;

			// track performance
			m_samples.push_back(currentPerformance);
			float median = MathUtil::median(m_samples);
			
			LogUtil::logMessage("current: %f ms, median: %f ms, samples: %d", currentPerformance, median, m_samples.size());
		}
	}
}