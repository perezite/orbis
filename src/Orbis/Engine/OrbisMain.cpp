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
		TimeManager* time = TimeManager::instance();

		m_numFrames = 0;
		bool hasQuitEvent = false;

		while (!hasQuitEvent)
		{
			time->update();
			input->update();
			level->update();
			level->render();

			if (m_onRenderedCallback)
				m_onRenderedCallback();

			hasQuitEvent = input->hasQuitEvent();
			logPerformance();
		}

		level->clear();
		input->clear();
	}

	void OrbisMain::logPerformance()
	{
		m_numFrames++;
		m_ticks += TimeManager::instance()->getDeltaTicks();
		if (m_ticks >= 1000)
		{
			float currentPerformance = (float)m_ticks / float(m_numFrames);
			m_samples.push_back(currentPerformance);
			float median = MathUtil::median(m_samples);

			m_ticks = 0;
			m_numFrames = 0;
			
			#if defined(ORBIS_LOG_PERFORMANCE)
				LogUtil::logMessage("current: %f ms, median: %f ms, samples: %d", currentPerformance, median, m_samples.size());
			#endif
		}
	}
}