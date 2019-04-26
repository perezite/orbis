#pragma once

namespace orb
{
	// provides functions related to time
	class TimeManager
	{
	public:
		// get the instance
		static TimeManager* instance();

		// update the time
		void update();

		// reset the time
		void reset();

		// get the seconds elapsed since the last time update()
		float getDeltaSeconds();

		// the the ticks elapsed since the last update()
		long getDeltaTicks();

		// simulate a fixed number of ticks per update. Can be used for testing/debugging. Zero ticks means a sregular (framerate-dependent) update
		void setFixedUpdateTime(long fixedTicks);

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