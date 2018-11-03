#include "Engine.h"

namespace orb
{
	Engine* Engine::instance()
	{
		static Engine instance;
		return &instance;
	}

	void Engine::heartbeat()
	{
	}
}

