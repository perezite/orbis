#pragma once

namespace orb
{
	class TimeManager
	{
	public:
		// get the instance
		static TimeManager* getInstance();

		// set a fixed number of ticks per update. Can be used for testing/debugging. Zero ticks means regular (dynamic update)
		void setFixedUpdate(long ticks);

		// update the level
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

		// number of ticks for fixed update
		long m_fixedTicks;
	};
}