#include "InputManager.h"

#include "../Video/VideoManager.h"
using namespace Video;

namespace 
{
	// convert pixel coordinates to screen coordinates in the range (-0.5, +0.5)
	Vector2D PixelCoordinatesToScreenCoordinates(int x, int y)
	{
		Vector2D resolution = VideoManager::GetInstance()->GetResolution();
		return Vector2D(float(x) / resolution.GetX() - 0.5f, float(y) / resolution.GetY() - 0.5f);
	}

	// convert the range (0, 1) to (-0.5, 0.5)
	Vector2D FingerCoordinatesToScreenCoordinates(float x, float y)
	{
		return Vector2D(x - 0.5f, y - 0.5f);
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
					m_taps.insert(event.tfinger.fingerId);
					break;
				case SDL_FINGERUP:
					m_taps.erase(event.tfinger.fingerId);
					break;
				case SDL_MOUSEBUTTONDOWN:
					m_taps.insert(event.button.button);
					break;
				case SDL_MOUSEBUTTONUP:
					m_taps.erase(event.button.button);
					break;
				case SDL_MOUSEMOTION:
					m_tapPosition = PixelCoordinatesToScreenCoordinates(event.motion.x, event.motion.y);
					break;
				case SDL_FINGERMOTION:
					m_tapPosition = FingerCoordinatesToScreenCoordinates(event.tfinger.x, event.tfinger.y);
			}
		}
	}

	bool InputManager::IsKeyDown(KeyCode keyCode)
	{
		return m_pressedKeys.count(keyCode) == 1;
	}

	bool InputManager::IsTapDown()
	{
		return m_taps.size() > 0;
	}

	Vector2D InputManager::GetTapPosition()
	{
		Exception::Assert(IsTapDown(), "GetTapPosition() can only be called when a tap is down");
		return m_tapPosition;
	}

}