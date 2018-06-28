#include "OrbisMain.h"

#include "../Core/TimeManager.h"
#include "../Core/LogHelper.h"
#include "../Game/LevelManager.h"
#include "../Input/InputManager.h"
#include "../Libraries/SDL.h"
#include "../Engine/Settings.h"
using namespace orbis::core;
using namespace orbis::game;
using namespace orbis::input;

namespace orbis
{
	namespace engine
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
				LogHelper::logMessage("%f ms/frame", currentPerformance);
				m_startTicks += 1000;
				m_numFrames = 0;

				// track average performance
				m_numSamples++;
				m_cumulativePerformance += currentPerformance;
				float average = m_cumulativePerformance / float(m_numSamples);
				LogHelper::logMessage("Average: %f ms/frame, samples: %d", average, m_numSamples);
			}
		}
	}
}