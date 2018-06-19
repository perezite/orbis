#include "TimeManager.h"

#include "../Libraries/SDL.h"

namespace Core
{
	TimeManager* TimeManager::getInstance()
	{
		static TimeManager instance;
		return &instance;
	}

	void TimeManager::update()
	{
		m_lastTicks = m_currentTicks;
		m_currentTicks = SDL_GetTicks();
	}

	void TimeManager::reset()
	{
		m_lastTicks = SDL_GetTicks();
	}

	float TimeManager::getDeltaSeconds()
	{
		return (m_currentTicks - m_lastTicks) / 1000.0f;
	}

	long TimeManager::getTicks()
	{
		return SDL_GetTicks();
	}

	TimeManager::TimeManager()
	{
		m_lastTicks = SDL_GetTicks();
	}
}
