#include "OrbisMain.h"

#include "../Core/TimeManager.h"
#include "../Core/LogHelper.h"
#include "../Game/LevelManager.h"
#include "../Input/InputManager.h"
#include "../Libraries/SDL.h"
#include "../Orbis/Settings.h"
using namespace Core;
using namespace Game;
using namespace Input;

namespace Orbis
{
	OrbisMain* OrbisMain::GetInstance()
	{
		static OrbisMain instance;
		return &instance;
	}

	void OrbisMain::Run()
	{
		LevelManager* level = LevelManager::GetInstance();
		InputManager* input = InputManager::GetInstance();

		m_startTicks = TimeManager::GetInstance()->GetTicks();
		m_numFrames = 0;

		while (true)
		{
			input->Update();
			if (input->HasQuitEvent())
				break;

			level->Update();
			level->Render();

			#if defined(ORBIS_LOG_PERFORMANCE)
				LogPerformance();
			#endif
		}

		level->Clear();
	}

	void OrbisMain::LogPerformance()
	{
		m_numFrames++;
		if (TimeManager::GetInstance()->GetTicks() - m_startTicks > 1000)
		{
			// track current performance
			float currentPerformance = 1000.0f / float(m_numFrames);
			LogHelper::LogMessage("%f ms/frame", currentPerformance);
			m_startTicks += 1000;
			m_numFrames = 0;

			// track average performance
			m_numSamples++;
			m_cumulativePerformance += currentPerformance;
			float average = m_cumulativePerformance / float(m_numSamples);
			LogHelper::LogMessage("Average: %f ms/frame, samples: %d", average, m_numSamples);
		}
	}	
}
