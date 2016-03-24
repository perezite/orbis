#pragma once

#include "SDLKeyCode.h"

#include <vector>
#include <SDL.h>

namespace Base
{
	class SDLEvent
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
		SDLEvent(SDL_Event sdlEvent) : m_sdlEvent(m_sdlEvent = sdlEvent) {}

		// Destructor
		virtual ~SDLEvent() {};

		// Get the event type
		Type GetType();

		// Get the keycode
		SDLKeyCode GetKeyCode();

	protected:
		// Assert that the SDLEvent is one of the given types
		void AssertType(std::vector<Type> types);

	private:
		SDL_Event m_sdlEvent;
	};
}