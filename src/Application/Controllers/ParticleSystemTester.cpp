#include "ParticleSystemTester.h"

#include "../../Base/Math/Math.h"
using namespace base::math;

#include "../../Orbis/Orbis.h"
using namespace orb::core;

#include <iostream>

namespace controllers
{
	float ParticleSystemTester::Speed = 1.0f;
	Vector2D ParticleSystemTester::TopTarget(0.5f, 0.5f);
	Vector2D ParticleSystemTester::BottomTarget(-0.5f, -0.5f);

	void ParticleSystemTester::update()
	{
		float dt = TimeManager::getInstance()->getDeltaSeconds();
		Vector2D dist = m_currentTarget - getParent()->getTransform()->position;
		Vector2D direction = dist.normalized();
		getParent()->getTransform()->position += direction * dt * 0.1f;

		if (Vector2D::distance(getParent()->getTransform()->position, TopTarget) < 0.001f)
			m_currentTarget = BottomTarget;
		else if (Vector2D::distance(getParent()->getTransform()->position, BottomTarget) < 0.001f)
			m_currentTarget = TopTarget;
	}
}

