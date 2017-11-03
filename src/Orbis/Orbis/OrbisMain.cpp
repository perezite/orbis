#include "OrbisMain.h"

#include "../Libraries/SDL.h"
#include "../Game/LevelManager.h"
using namespace Game;
using namespace Libraries;

namespace Orbis
{
	OrbisMain* OrbisMain::GetInstance()
	{
		static OrbisMain instance;
		return &instance;
	}

	void OrbisMain::Run()
	{
		LevelManager* levelManager = LevelManager::GetInstance();

		bool done = false;
		SDL_Event event;
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
		}
	}
}
