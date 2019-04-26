#include "ParticleSystemTester.h"

#include "../../Base/Base.h"
using namespace base;

#include "../../Orbis/Orbis.h"
using namespace orb;

#include <iostream>

namespace app
{
	float ParticleSystemTester::Speed = 1.0f;
	Vector2f ParticleSystemTester::TopTarget(0.5f, 0.5f);
	Vector2f ParticleSystemTester::BottomTarget(-0.5f, -0.5f);

	void ParticleSystemTester::update()
	{
		float dt = TimeManager::instance()->getDeltaSeconds();
		Vector2f dist = m_currentTarget - getParent()->getTransform()->position;
		Vector2f direction = dist.normalized();
		getParent()->getTransform()->position += direction * dt * 0.1f;

		if (Vector2f::distance(getParent()->getTransform()->position, TopTarget) < 0.001f)
			m_currentTarget = BottomTarget;
		else if (Vector2f::distance(getParent()->getTransform()->position, BottomTarget) < 0.001f)
			m_currentTarget = TopTarget;
	}
}

