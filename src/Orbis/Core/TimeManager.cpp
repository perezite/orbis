#include "TimeManager.h"

#include "../Libraries/SDL.h"

namespace orb
{
	TimeManager* TimeManager::getInstance()
	{
		static TimeManager instance;
		return &instance;
	}

	void TimeManager::setFixedUpdate(long ticks)
	{
		m_fixedTicks = ticks;
		reset();
	}

	void TimeManager::update()
	{
		m_lastTicks = m_currentTicks;
		m_currentTicks = m_fixedTicks == 0 ? SDL_GetTicks() : (m_currentTicks + m_fixedTicks);
	}

	void TimeManager::reset()
	{
		m_lastTicks = SDL_GetTicks();
		m_currentTicks = SDL_GetTicks();
	}

	float TimeManager::getDeltaSeconds()
	{
		return (m_currentTicks - m_lastTicks) / 1000.0f;
	}

	long TimeManager::getTicks()
	{
		return m_fixedTicks == 0 ? SDL_GetTicks() : m_currentTicks;
	}

	TimeManager::TimeManager() : m_fixedTicks(0)
	{
		reset();
	}
}
