#include "WobbleEffect.h"

#include "../../Base/Math/MathUtil.h"
using namespace base;

#include "../../Orbis/Orbis.h"
using namespace orb;

#include <cstdlib>

namespace app
{
	const float WobbleEffect::MIN_SCALE = 0.02f;
	const float WobbleEffect::MAX_SCALE = 0.1f;

	void WobbleEffect::start()
	{
		float scale = MIN_SCALE + (MAX_SCALE - MIN_SCALE) * MathUtil::getRandom();
		getParent()->getTransform()->scale = Vector2D(scale, scale);
		m_isGrowing = rand() % 2 == 0 ? true : false;
	}

	void WobbleEffect::update()
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
