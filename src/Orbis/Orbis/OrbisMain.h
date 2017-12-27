#pragma once

#include "../Video/VideoManager.h"
using namespace Video;

namespace Orbis
{
	class OrbisMain
	{
	public:
		// get instance
		static OrbisMain* GetInstance();

		// destructor
		virtual ~OrbisMain() { };

		// initialize
		void Initialize();

		// run the engine
		void Run();

	protected:
		// log the performance 
			void LogPerformance();

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