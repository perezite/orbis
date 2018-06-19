#include "ParticleSystemTester.h"

#include "../../Base/Math/MathHelper.h"
using namespace Math;

#include "../../Orbis/Core/TimeManager.h"
using namespace Core;

#include <iostream>

namespace Controllers
{
	float ParticleSystemTester::Speed = 1.0f;
	Vector2D ParticleSystemTester::TopTarget(0.5f, 0.5f);
	Vector2D ParticleSystemTester::BottomTarget(-0.5f, -0.5f);

	void ParticleSystemTester::Update()
	{
		float dt = TimeManager::getInstance()->GetDeltaSeconds();
		Vector2D dist = m_currentTarget - GetParent()->getTransform()->position;
		Vector2D direction = dist.Normalized();
		GetParent()->getTransform()->position += direction * dt * 0.1f;

		if (Vector2D::Distance(GetParent()->getTransform()->position, TopTarget) < 0.001f)
			m_currentTarget = BottomTarget;
		else if (Vector2D::Distance(GetParent()->getTransform()->position, BottomTarget) < 0.001f)
			m_currentTarget = TopTarget;
	}
}

