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

		// is key pressed
		bool IsKeyPressed(KeyCode keyCode);

		// is a tap pressed
		bool IsTapPressed();

		// is a tap down
		bool IsTapDown();

		// get the normalized tap position
		Vector2D GetTapPosition();

	private:
		// list of currently pressed keys
		std::set<KeyCode> m_pressedKeys;

		// list of currently pressed taps
		std::set<Sint64> m_pressedTaps;

		// list of taps down 
		std::set<Sint64> m_tapsDown;

		// the last recorded tap position
		Vector2D m_tapPosition;

		// has the input a quit event
		bool m_hasQuitEvent;
	};
}
