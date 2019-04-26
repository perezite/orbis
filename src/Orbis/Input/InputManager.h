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
		static InputManager* instance();

		// update
		void update();

		// clear
		void clear();

		// has the input a quit event
		bool hasQuitEvent() const { return m_hasQuitEvent; }

		// set the quit event to true
		void setQuitEvent(bool hasQuitEvent);

		// is key pressed
		bool isKeyDown(KeyCode keyCode) const;

		// is key going down
		bool isKeyGoingDown(KeyCode keyCode) const;

		// is a tap happening
		bool isTapDown() const;

		// is a tap happening within the given rect
		bool isTapDown(Rect rect) const;

		// is a tap index pressed
		bool isTapIndexDown(signed long index) const;

		// is a tap going down
		bool isTapGoingDown() const;

		// is a tap going down in the given rect
		bool isTapGoingDown(Rect rect) const;

		// is a tap index going down
		bool isTapIndexGoingDown(signed long index) const;

		// get the tap position in camera space ((+/-0.5f, +/-0.5f * aspectRation)) 
		const Vector2f getTapPosition() const;

		// get an input line from console
		const std::string getConsoleLine(std::string promptMessage) const;

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
