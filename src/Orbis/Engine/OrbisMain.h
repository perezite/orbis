#pragma once

#include "../Video/VideoManager.h"

namespace orb
{
	class OrbisMain
	{
	public:
		// get instance
		static OrbisMain* getInstance();

		// destructor
		virtual ~OrbisMain() { };

		// run the engine
		void run();

		// set an callback which is called after each rendering cycle. Can be used for testing.
		 void setOnRenderedCallback(void(*callback)(void)) { m_onRenderedCallback = callback; }

	protected:
		// singleton ctor
		OrbisMain() : m_onRenderedCallback(NULL)
		{ }

		// log the performance
		void logPerformance();

	private:
		// start time of current performance log measurement
		long m_startTicks;

		// number of frames elapsed since last performance log updateLevel
		long m_numFrames;

		// performance samples
		std::vector<float> m_samples;

		// blub 
		void (*m_onRenderedCallback)(void);
	};
}