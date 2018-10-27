#pragma once

#include "KeyCode.h"

#include "../Game/TransformSpace.h"

#include "../../Base/Base.h"
using namespace base;

#include <set>
#include <string>

namespace orb
{
	class InputManager
	{
	public:
		// get instance
		static InputManager* getInstance();

		// update
		void update();

		// clear
		void clear();

		// has the input a quit event
		bool hasQuitEvent() const { return m_hasQuitEvent; }

		// set the quit event to true
		void setQuitEvent();

		// is key pressed
		bool isKeyDown(KeyCode keyCode);

		// is key going down
		bool isKeyGoingDown(KeyCode keyCode);

		// is a tap pressed
		bool isTapDown();

		// is a tap pressed in cam coordinates rect
		bool isTapDown(Rect rect);

		// is a tap index pressed
		bool isTapIndexDown(signed long index);

		// is a tap going down
		bool isTapGoingDown();

		// is a tap going down in cam coordinates rect
		bool isTapGoingDown(Rect rect);

		// is a tap index going down
		bool isTapIndexGoingDown(signed long index);

		// get the tap position in camera space ((+/-0.5f, +/-0.5f * aspectRation)) 
		Vector2f getTapPosition();

		// get an input line from console
		std::string getConsoleLine(std::string promptMessage);

	protected:
		// singleton ctor
		InputManager() :
			m_isCursorInsideWindow(true)
		{};

	private:
		// list of currently pressed keys
		std::set<KeyCode> m_keysDown;

		// list of keys going down
		std::set<KeyCode> m_keysGoingDown;

		// list of currently pressed taps
		std::set<Sint64> m_tapsDown;

		// list of taps going down 
		std::set<Sint64> m_tapsGoingDown;

		// the last recorded tap position
		Vector2f m_tapPosition;

		// is cursor inside the window
		bool m_isCursorInsideWindow;

		// has the input a quit event
		bool m_hasQuitEvent;
	};
}
