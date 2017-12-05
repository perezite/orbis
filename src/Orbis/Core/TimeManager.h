#pragma once

namespace Core
{
	class TimeManager
	{
	public:
		// get the instance
		static TimeManager* GetInstance();

		// update
		void Update();

		// reset
		void Reset();

		// get the seconds elapsed since the last frame
		float GetDeltaSeconds();

		// get the current time in seconds
		long GetTicks();

	protected:
		// singleton ctor
		TimeManager();

	private:
		// number of ticks at the beginning of the previous frame
		long m_lastTicks;

		// number of ticks at beginning of the current frame
		long m_currentTicks;
	};
}