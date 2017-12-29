#pragma once

#include "KeyCode.h"

#include "../../Base/Math/Vector2D.h"
using namespace Math;

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

		// set the quit event to true
		void SetQuitEvent();

		// is key pressed
		bool IsKeyDown(KeyCode keyCode);

		// is key going down
		bool IsKeyGoingDown(KeyCode keyCode);

		// is a tap pressed
		bool IsTapDown();

		// is a tap going down
		bool IsTapGoingDown();

		// get the normalized tap position
		Vector2D GetTapPosition();

	private:
		// singleton ctor
		InputManager() : m_isCursorInsideWindow(true) {};

		// list of currently pressed keys
		std::set<KeyCode> m_keysDown;

		// list of keys going down
		std::set<KeyCode> m_keysGoingDown;

		// list of currently pressed taps
		std::set<Sint64> m_tapsDown;

		// list of taps going down 
		std::set<Sint64> m_tapsGoingDown;

		// the last recorded tap position
		Vector2D m_tapPosition;

		// is cursor inside the window
		bool m_isCursorInsideWindow;

		// has the input a quit event
		bool m_hasQuitEvent;
	};
}
