#include "InputManager.h"

#include "..\Base\SDLAdapter.h"

using namespace Base;

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
		SDL_Event e;

		while (SDLAdapter::HasPendingEvents())
		{
			e = SDLAdapter::PollEvent();

			if (e.type == SDL_QUIT)
			{
				m_IsQuit = true;
			}
		}	
	}

	bool InputManager::IsKeyDown()
	{
		return false;
	}

	bool InputManager::IsKeyTapped()
	{
		return false;
	}

	bool InputManager::TempIsQuit()
	{
		return m_IsQuit;
	}
}