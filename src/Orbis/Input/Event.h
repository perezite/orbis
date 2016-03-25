#pragma once

#include "EventAdapter.h"

#include <vector>
#include <SDL.h>

namespace Input
{
	// adapter for sdl events
	class Event
	{
	public:
		enum Type
		{
			KeyDown,
			KeyUp,
			Quit,
			Unknown
		};

	public:
		// Constructor
		Event(SDL_Event sdlEvent) : m_sdlEvent(m_sdlEvent = sdlEvent) {}

		// Destructor
		virtual ~Event() {};

		// Get the event type
		Type GetType();

		// Get the keycode
		KeyCode GetKeyCode();

	protected:
		// Assert that the SDLEvent is one of the given types
		void AssertType(std::vector<Type> types);

	private:
		SDL_Event m_sdlEvent;
	};
}