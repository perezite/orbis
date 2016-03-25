#include "EventAdapter.h"

#include "Event.h"

#include "..\Core\Exception.h"
using namespace Core;

namespace Input
{
	bool EventAdapter::HasPendingEvents()
	{
		return SDL_PollEvent(NULL) == 1;
	}

	Event EventAdapter::PollEvent()
	{
		SDL_Event e;

		int result = SDL_PollEvent(&e);

		if (result == 0)
		{
			throw Exception("SDLAdapter::PollEvent has been called, but there are no events. Use SDLAdapter::HasPendingEvents before polling.");
		}

		return Event(e);
	}
}