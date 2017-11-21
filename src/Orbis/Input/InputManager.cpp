#include "InputManager.h"

namespace Input
{
	InputManager* InputManager::GetInstance()
	{
		static InputManager instance;

		return &instance;
	}

	void InputManager::Update()
	{
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					m_hasQuitEvent = true;
					break;
				case SDL_KEYDOWN:
					m_pressedKeys.insert((KeyCode)event.key.keysym.sym);
					break;
				case SDL_KEYUP:
					m_pressedKeys.erase((KeyCode)event.key.keysym.sym);
					break;
				case SDL_FINGERDOWN:
					m_touches.insert(event.tfinger.fingerId);
					break;
				case SDL_FINGERUP:
					m_touches.erase(event.tfinger.fingerId);
					break;
				case SDL_MOUSEBUTTONDOWN:
					m_clicks.insert(event.button.button);
					break;
				case SDL_MOUSEBUTTONUP:
					m_clicks.erase(event.button.button);
					break;
			}
		}
	}

	bool InputManager::IsKeyDown(KeyCode keyCode)
	{
		return m_pressedKeys.count(keyCode) == 1;
	}

	bool InputManager::IsTapDown()
	{
		return m_touches.size() > 0 || m_clicks.size() > 0;
	}

}