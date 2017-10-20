#include "TimeManager.h"

#include "../Libraries/SDL.h"
using namespace Libraries;

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
		m_currentTicks = SDL::GetTicks();
	}

	void TimeManager::Reset()
	{
		m_lastTicks = SDL::GetTicks();
	}

	float TimeManager::GetDeltaSeconds()
	{
		return (m_currentTicks - m_lastTicks) / 1000.0f;
	}

	TimeManager::TimeManager()
	{
		m_lastTicks = SDL::GetTicks();
	}
}
