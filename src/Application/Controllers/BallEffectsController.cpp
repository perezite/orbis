#include "BallEffectsController.h"

#include "../../Orbis/Core/LogHelper.h"
#include "../../Orbis/Core/TimeManager.h"
using namespace Core;

#define __STATE_EXPLODING

namespace Controllers
{
	#ifdef __STATE_EXPLODING

		bool BallEffectsController::Explode()
		{
			float waitSeconds = 2.0f - m_explosionTimeElapsed;
			LogHelper::LogMessage("BallEffectsController::ExplodingRun(), wait another %f", waitSeconds);
			m_explosionTimeElapsed += TimeManager::getInstance()->GetDeltaSeconds();

			if (m_explosionTimeElapsed >= 2.0f)
			{
				m_explosionTimeElapsed = 0.0f;
				return false;
			}

			return true;
		}

	#endif
}
