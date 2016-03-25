#include "InputManager.h"

#include "Event.h"

#include <iostream>

namespace Input
{
	InputManager::InputManager()
	{
	}

	InputManager::~InputManager()
	{
	}

	InputManager* InputManager::GetInstance()
	{
		static InputManager instance;

		return &instance;
	}

	void InputManager::Update()
	{
		while (EventAdapter::HasPendingEvents())
		{
			Event event = EventAdapter::PollEvent();

			switch (event.GetType())
			{
			case Event::Type::Quit:
				m_hasQuitEvent = true;
				break;
			case Event::Type::KeyDown:
				m_pressedKeys.insert_or_assign(event.GetKeyCode(), true);
				break;
			case Event::Type::KeyUp:
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