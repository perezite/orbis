#include "OrbisMain.h"

#include "../Core/TimeManager.h"
#include "../Core/LogHelper.h"
#include "../Libraries/SDL.h"
#include "../Game/LevelManager.h"
using namespace Core;
using namespace Game;

namespace Orbis
{
	OrbisMain* OrbisMain::GetInstance()
	{
		static OrbisMain instance;
		return &instance;
	}

	void OrbisMain::Run()
	{
		long numFrames = 0;
		bool done = false;
		SDL_Event event;
		LevelManager* levelManager = LevelManager::GetInstance();
		TimeManager* timeManager = TimeManager::GetInstance();

		long start = TimeManager::GetInstance()->GetTicks();
		while (!done)
		{
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT || event.type == SDL_FINGERDOWN)
				{
					done = true;
				}
			}

			levelManager->Heartbeat();

			#if defined(_DEBUG)
				numFrames++;
				if (timeManager->GetTicks() - start > 1000)
				{
					LogHelper::LogMessage("%f ms/frame", 1000.0 / double(numFrames));
					start += 1000;
					numFrames = 0;
				}
			#endif
		}
	}
}
