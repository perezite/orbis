#pragma once

#include "KeyCode.h"

#include <set>

namespace Input
{
	class InputManager
	{
	public:
		// get instance
		static InputManager* GetInstance();

		// update
		void Update();

		// has the input a quit event
		bool HasQuitEvent() const { return m_hasQuitEvent; }

		// is key down
		bool IsKeyDown(KeyCode keyCode);

		// has the input a tap event
		bool IsTapDown();

	private:
		// list of currently pressed keys
		std::set<KeyCode> m_pressedKeys;

		// list of current touches
		std::set<SDL_FingerID> m_touches;

		// list of current clicks
		std::set<Uint8> m_clicks;

		// has the input a quit event
		bool m_hasQuitEvent;
	};
}
