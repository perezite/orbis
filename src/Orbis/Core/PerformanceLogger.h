#include <vector>

namespace orb
{
	class PerformanceLogger
	{
	public:
		// ctor
		PerformanceLogger() : m_numFrames(0), m_ticks(0)
		{};

		// log current performance
		void log();

	private: 
		// number of frames elapsed since last performance log update
		long m_numFrames;

		// number of ticks elapsed since last performance log update
		long m_ticks;

		// performance samples
		std::vector<float> m_samples;
	};
}