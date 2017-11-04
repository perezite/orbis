#include "TimeManager.h"

#include "../Libraries/SDL.h"

namespace Core
{
	TimeManager* TimeManager::GetInstance()
	{
		static TimeManager instance;
		return &instance;
	}

	void TimeManager::Update()
	{
		m_lastTicks = m_currentTicks;
		m_currentTicks = SDL_GetTicks();
	}

	void TimeManager::Reset()
	{
		m_lastTicks = SDL_GetTicks();
	}

	float TimeManager::GetDeltaSeconds()
	{
		return (m_currentTicks - m_lastTicks) / 1000.0f;
	}

	TimeManager::TimeManager()
	{
		m_lastTicks = SDL_GetTicks();
	}
}
