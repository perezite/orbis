#pragma once

#include "KeyCode.h"

#include "EventAdapter.h"

#include <map>

namespace Input
{
	class InputManager
	{
	public:
		// get instance
		static InputManager* GetInstance();

		// update
		void Update();

		// is key down
		bool IsKeyDown(KeyCode keyCode);

		// has manager caught a quit event
		bool HasQuitEvent();

		// Destructor
		virtual ~InputManager();

	protected:
		// Singleton Constructor
		InputManager();

	private:
		// has manager caught a quit event
		bool m_hasQuitEvent;

		// pressed keys
		std::map<KeyCode, bool> m_pressedKeys;
	};
}