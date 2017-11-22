#include "OrbisMain.h"

#include "../Core/TimeManager.h"
#include "../Core/LogHelper.h"
#include "../Game/LevelManager.h"
#include "../Input/InputManager.h"
#include "../Libraries/SDL.h"
#include "../Settings/Settings.h"
using namespace Core;
using namespace Game;
using namespace Input;

namespace
{
	// start time of current performance log measurement
	long start;

	// number of frames elapsed since last performance log update
	long numFrames;

	// the time manager
	TimeManager* timeManager = TimeManager::GetInstance();

	#if defined(ORBIS_LOG_PERFORMANCE)
		inline void LogPerformance()
		{
			numFrames++;
			if (timeManager->GetTicks() - start > 1000)
			{
				LogHelper::LogMessage("%f ms/frame", 1000.0 / double(numFrames));
				start += 1000;
				numFrames = 0;
			}
		}
	#endif
}

namespace Orbis
{
	OrbisMain* OrbisMain::GetInstance()
	{
		static OrbisMain instance;
		return &instance;
	}

	void OrbisMain::Initialize()
	{
		VideoManager::GetInstance()->Initialize();
	}

	void OrbisMain::Run()
	{
		LevelManager* levelManager = LevelManager::GetInstance();
		InputManager* inputManager = InputManager::GetInstance();

		start = timeManager->GetTicks();
		numFrames = 0;

		while (true)
		{
			inputManager->Update();
			if (inputManager->HasQuitEvent())
				break;

			levelManager->Update();

			#if defined(ORBIS_LOG_PERFORMANCE)
				LogPerformance();
			#endif
		}
	}
}
