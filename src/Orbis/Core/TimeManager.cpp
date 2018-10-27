#include "TimeManager.h"

#include "../Libraries/SDL.h"

#include <assert.h>

namespace orb
{
	TimeManager* TimeManager::instance()
	{
		static TimeManager instance;
		return &instance;
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
		return (getDeltaTicks()) / 1000.0f;
	}

	long TimeManager::getDeltaTicks()
	{
		return m_currentTicks - m_lastTicks;
	}

	void TimeManager::setFixedUpdateTime(long fixedTicks)
	{
		m_fixedTicks = fixedTicks;
		reset();
	}

	TimeManager::TimeManager() : m_fixedTicks(0)
	{
		reset();
	}
}
