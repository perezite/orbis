#include "BallEffectsController.h"

#include "../../Orbis/Core/LogHelper.h"
#include "../../Orbis/Core/TimeManager.h"
using namespace core;

#define __STATE_EXPLODING

namespace controllers
{
	#ifdef __STATE_EXPLODING

		bool BallEffectsController::explode()
		{
			float waitSeconds = 2.0f - m_explosionTimeElapsed;
			LogHelper::logMessage("BallEffectsController::ExplodingRun(), wait another %f", waitSeconds);
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
