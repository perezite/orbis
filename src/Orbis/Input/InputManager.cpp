#include "InputManager.h"

#include "../Video/VideoManager.h"
#include "../Components/Camera.h"

namespace 
{
	using namespace orb;

	// convert pixel coordinates to screen coordinates in the range (-0.5, +0.5)
	Vector2D PixelCoordinatesToScreenCoordinates(int x, int y)
	{
		Vector2D resolution = VideoManager::getInstance()->getWindow()->getResolution();
		return Vector2D(float(x) / resolution.x - 0.5f, 0.5f - float(y) / resolution.y);
	}

	// convert finger coordinates to screen coordinates in the range (-0.5, +0.5)
	Vector2D FingerCoordinatesToScreenCoordinates(float x, float y)
	{
		return Vector2D(x - 0.5f, 0.5f - y);
	}
}

namespace orb
{
	InputManager* InputManager::getInstance()
	{
		static InputManager instance;

		return &instance;
	}

	void InputManager::update()
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

	void InputManager::clear()
	{
		m_keysDown.clear();
		m_keysGoingDown.clear();
		m_tapsDown.clear();
		m_tapsGoingDown.clear();
		m_isCursorInsideWindow = false;
		m_hasQuitEvent = false;
	}

	void InputManager::setQuitEvent()
	{
		m_hasQuitEvent = true;
	}

	bool InputManager::isKeyDown(KeyCode keyCode)
	{
		return m_keysDown.count(keyCode) == 1;
	}

	bool InputManager::isKeyGoingDown(KeyCode keyCode)
	{
		return m_keysGoingDown.count(keyCode) == 1;
	}

	bool InputManager::isTapDown()
	{
		return m_isCursorInsideWindow && m_tapsDown.size() > 0;
	}

	bool InputManager::isTapDown(Rect rect)
	{
		if (isTapDown())
		{
			if (rect.contains(getTapPosition()))
				return true;
		}

		return false;
	}

	bool InputManager::isTapIndexDown(signed long index)
	{
		return m_tapsDown.find(index) != m_tapsDown.end();
	}

	bool InputManager::isTapGoingDown()
	{
		return m_isCursorInsideWindow && m_tapsGoingDown.size() > 0;
	}

	bool InputManager::isTapGoingDown(Rect rect)
	{
		if (isTapGoingDown())
		{
			if (rect.contains(getTapPosition()))
				return true;
		}

		return false;
	}

	bool InputManager::isTapIndexGoingDown(signed long index)
	{
		return m_tapsGoingDown.find(index) != m_tapsGoingDown.end();
	}

	Vector2D InputManager::getTapPosition()
	{
		Exception::assert(isTapDown() || isTapGoingDown(), "getTapPosition() can only be called when a tap is pressed or going down");

		Camera* cam = Camera::getInstance();
		float aspect = cam->getAspect();
		return Vector2D(m_tapPosition.x, aspect * m_tapPosition.y);
	}
}