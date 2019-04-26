#include "PerformanceLogger.h"

#include "TimeManager.h"
#include "LogUtil.h"
#include "../Engine/Settings.h"

#include "../../Base/Math/MathUtil.h"
using namespace base;

namespace orb
{
	void PerformanceLogger::log()
	{
		m_numFrames++;
		m_ticks += TimeManager::instance()->getDeltaTicks();
		if (m_ticks >= 1000)
		{
			float currentPerformance = (float)m_ticks / float(m_numFrames);
			m_samples.push_back(currentPerformance);
			float median = MathUtil::median(m_samples);

			m_ticks = 0;
			m_numFrames = 0;

			#if defined(ORBIS_LOG_PERFORMANCE)
				LogUtil::logMessage("current: %f ms, median: %f ms, samples: %d", currentPerformance, median, m_samples.size());
			#endif
		}
	}
}
