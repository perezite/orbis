#include "InputManager.h"

#include "../Video/VideoManager.h"
#include "../Components/Camera.h"
using namespace Video;
using namespace Components;

namespace 
{
	// convert pixel coordinates to screen coordinates in the range (-0.5, +0.5)
	Vector2D PixelCoordinatesToScreenCoordinates(int x, int y)
	{
		Vector2D resolution = VideoManager::GetInstance()->GetResolution();
		return Vector2D(float(x) / resolution.x - 0.5f, 0.5f - float(y) / resolution.y);
	}

	// convert finger coordinates to screen coordinates in the range (-0.5, +0.5)
	Vector2D FingerCoordinatesToScreenCoordinates(float x, float y)
	{
		return Vector2D(x - 0.5f, 0.5f - y);
	}
}

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

		m_tapsGoingDown.clear();
		m_keysGoingDown.clear();

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					m_hasQuitEvent = true;
					break;
				case SDL_KEYDOWN:
					m_keysDown.insert((KeyCode)event.key.keysym.sym);
					m_keysGoingDown.insert((KeyCode)event.key.keysym.sym);
					break;
				case SDL_KEYUP:
					m_keysDown.erase((KeyCode)event.key.keysym.sym);
					break;
				case SDL_FINGERDOWN:
					m_tapsDown.insert(event.tfinger.fingerId);
					m_tapsGoingDown.insert(event.tfinger.fingerId);
					break;
				case SDL_FINGERUP:
					m_tapsDown.erase(event.tfinger.fingerId);
					break;
				case SDL_MOUSEBUTTONDOWN:
					m_tapsDown.insert(event.button.button);
					m_tapsGoingDown.insert(event.button.button);
					break;
				case SDL_MOUSEBUTTONUP:
					m_tapsDown.erase(event.button.button);
					break;
				case SDL_MOUSEMOTION:
					m_tapPosition = PixelCoordinatesToScreenCoordinates(event.motion.x, event.motion.y);
					break;
				case SDL_FINGERMOTION:
					m_tapPosition = FingerCoordinatesToScreenCoordinates(event.tfinger.x, event.tfinger.y);
					break;
				case SDL_WINDOWEVENT:
					switch (event.window.event)
					{
						case SDL_WINDOWEVENT_ENTER:
							m_isCursorInsideWindow = true;
							break;
						case SDL_WINDOWEVENT_LEAVE:
							m_isCursorInsideWindow = false;
							m_tapsDown.clear();
							m_tapsGoingDown.clear();
							break;
					}
					break;
			}
		}
	}

	void InputManager::SetQuitEvent()
	{
		m_hasQuitEvent = true;
	}

	bool InputManager::IsKeyDown(KeyCode keyCode)
	{
		return m_keysDown.count(keyCode) == 1;
	}

	bool InputManager::IsKeyGoingDown(KeyCode keyCode)
	{
		return m_keysGoingDown.count(keyCode) == 1;
	}

	bool InputManager::IsTapDown()
	{
		return m_isCursorInsideWindow && m_tapsDown.size() > 0;
	}

	bool InputManager::IsTapIndexDown(signed long index)
	{
		return m_tapsDown.find(index) != m_tapsDown.end();
	}

	bool InputManager::IsTapGoingDown()
	{
		return m_isCursorInsideWindow && m_tapsGoingDown.size() > 0;
	}

	bool InputManager::IsTapIndexGoingDown(signed long index)
	{
		return m_tapsGoingDown.find(index) != m_tapsGoingDown.end();
	}

	Vector2D InputManager::GetTapPosition()
	{
		Exception::Assert(IsTapDown(), "GetTapPosition() can only be called when a tap is pressed or going down");
		
		return m_tapPosition;
	}

	Vector2D InputManager::GetAspectCorrectedTapPosition()
	{
		Vector2D tapPos = GetTapPosition();
		Camera* cam = Camera::GetInstance();
		float aspect = cam->GetAspect();
		return Vector2D(tapPos.x, aspect * tapPos.y);
	}
}