#include "BallEffects.h"

#include "../../Orbis/Orbis.h"
using namespace orb::core;

#define __STATE_EXPLODING

namespace app
{
	#ifdef __STATE_EXPLODING

		bool BallEffects::explode()
		{
			float waitSeconds = 2.0f - m_explosionTimeElapsed;
			LogUtil::logMessage("BallEffects::ExplodingRun(), wait another %f", waitSeconds);
			m_explosionTimeElapsed += TimeManager::getInstance()->getDeltaSeconds();

			if (m_explosionTimeElapsed >= 2.0f)
			{
				m_explosionTimeElapsed = 0.0f;
				return false;
			}

			return true;
		}

	#endif
}
