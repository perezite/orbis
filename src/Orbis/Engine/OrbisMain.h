#pragma once

#include "../Video/VideoManager.h"
using namespace orb::video;

namespace orb
{
	namespace engine
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

		protected:
			// log the performance 
			void logPerformance();

		private:
			// start time of current performance log measurement
			long m_startTicks;

			// number of frames elapsed since last performance log update
			long m_numFrames;

			// current number of performance samples
			long m_numSamples;

			// cumulated performance values
			float m_cumulativePerformance;
		};
	}
}