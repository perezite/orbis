#include "WobbleController.h"

#include "../../Orbis/Orbis.h"
using namespace orb::core;
using namespace orb::game;

#include "../../Base/Math/MathHelper.h"
using namespace base::math;

#include <cstdlib>

namespace controllers
{
	const float WobbleController::MIN_SCALE = 0.02f;
	const float WobbleController::MAX_SCALE = 0.1f;

	void WobbleController::start()
	{
		float scale = MIN_SCALE + (MAX_SCALE - MIN_SCALE) * MathHelper::getRandom();
		getParent()->getTransform()->scale = Vector2D(scale, scale);
		m_isGrowing = rand() % 2 == 0 ? true : false;
	}

	void WobbleController::update()
	{
		float dt = TimeManager::getInstance()->getDeltaSeconds();
		Transform* trans = getParent()->getTransform();

		float deltaScale = m_isGrowing ? dt * 0.01f : dt * -0.01f;
		getParent()->getTransform()->scale += Vector2D(deltaScale, deltaScale);

		if (trans->scale.x < MIN_SCALE)
			m_isGrowing = true;

		if (trans->scale.x > MAX_SCALE)
			m_isGrowing = false;
	}
}
