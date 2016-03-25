#include "InputManager.h"

#include <iostream>

namespace Input
{
	InputManager::InputManager()
	{
	}

	InputManager::~InputManager()
	{
	}

	InputManager& InputManager::GetInstance()
	{
		static InputManager instance;

		return instance;
	}

	void InputManager::Update()
	{
		while (SDLAdapter::HasPendingEvents())
		{
			SDLEvent event = SDLAdapter::PollEvent();

			switch (event.GetType())
			{
			case SDLEvent::Type::Quit:
				m_hasQuitEvent = true;
				break;
			case SDLEvent::Type::KeyDown:
				m_pressedKeys.insert_or_assign(event.GetKeyCode(), true);
				break;
			case SDLEvent::Type::KeyUp:
				m_pressedKeys.insert_or_assign(event.GetKeyCode(), false);
				break;
			}	
		}	
	}

	bool InputManager::IsKeyDown(KeyCode keyCode)
	{
		if (m_pressedKeys.find(keyCode) == m_pressedKeys.end())
		{
			m_pressedKeys.insert_or_assign(keyCode, false);
		}

		return m_pressedKeys.at(keyCode);
	}

	bool InputManager::HasQuitEvent()
	{
		return m_hasQuitEvent;
	}
}