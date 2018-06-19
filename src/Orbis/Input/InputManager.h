#pragma once

#include "KeyCode.h"

#include "../Game/TransformSpace.h"
using namespace Game;

#include "../../Base/Math/Vector2D.h"
#include "../../Base/Math/Rect.h"
using namespace Math;

#include <set>

namespace Input
{
	class InputManager
	{
	public:
		// get instance
		static InputManager* getInstance();

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

		// is a tap pressed in cam coordinates rect
		bool IsTapDown(Rect rect);

		// is a tap index pressed
		bool IsTapIndexDown(signed long index);

		// is a tap going down
		bool IsTapGoingDown();

		// is a tap going down in cam coordinates rect
		bool IsTapGoingDown(Rect rect);

		// is a tap index going down
		bool IsTapIndexGoingDown(signed long index);

		// get the tap position in camera space ((+/-0.5f, +/-0.5f * aspectRation)) 
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
