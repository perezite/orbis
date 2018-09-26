#pragma once

namespace orb
{
	class TimeManager
	{
	public:
		// get the instance
		static TimeManager* getInstance();

		// updateLevel
		void update();

		// reset
		void reset();

		// get the seconds elapsed since the last frame
		float getDeltaSeconds();

		// get the current time in seconds
		long getTicks();

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