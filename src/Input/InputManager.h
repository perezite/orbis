#pragma once

#include "..\Base\SDLAdapter.h"
using namespace Base;

#include <map>

namespace Input
{
	class InputManager
	{
	public:
		// get instance
		static InputManager& GetInstance();

		// update
		void Update();

		// is key down
		bool IsKeyDown(SDLKeyCode keyCode);

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
		std::map<SDLKeyCode, bool> m_pressedKeys;
	};
}