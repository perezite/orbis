#include "OrbisMain.h"

#include "../Game/LevelManager.h"
using namespace Game;

#include "SDL2/SDL.h"

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
				if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN || event.type == SDL_FINGERDOWN)
				{
					done = true;
				}
			}

			levelManager->Heartbeat();
		}
	}
}
