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
		
		// set a callback which is called after each rendering cycle. Can be used for testing.
		 void setOnRenderedCallback(void(*callback)(void)) { m_onRenderedCallback = callback; }

	protected:
		// singleton ctor
		OrbisMain() : m_onRenderedCallback(NULL), m_numFrames(0), m_ticks(0)
		{ }

		// log the performance
		void logPerformance();

	private:
		// number of frames elapsed since last performance log update
		long m_numFrames;

		// number of ticks elapsed since last performance log update
		long m_ticks;

		// performance samples
		std::vector<float> m_samples;

		// callback called after each redendering cycle
		void (*m_onRenderedCallback)(void);
	};
}