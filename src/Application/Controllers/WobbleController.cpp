#include "WobbleController.h"

#include "../../Orbis/Core/TimeManager.h"
#include "../../Orbis/Game/Entity.h"
using namespace Core;
using namespace Game;

#include "../../Base/Math/MathHelper.h"
using namespace Math;

#include <cstdlib>

namespace Controllers
{
	const float WobbleController::MIN_SCALE = 0.02f;
	const float WobbleController::MAX_SCALE = 0.1f;

	void WobbleController::start()
	{
		float scale = MIN_SCALE + (MAX_SCALE - MIN_SCALE) * MathHelper::GetRandom();
		GetParent()->GetTransform()->scale = Vector2D(scale, scale);
		m_isGrowing = rand() % 2 == 0 ? true : false;
	}

	void WobbleController::Update()
	{
		float dt = TimeManager::getInstance()->GetDeltaSeconds();
		Transform* trans = GetParent()->GetTransform();

		float deltaScale = m_isGrowing ? dt * 0.01f : dt * -0.01f;
		GetParent()->GetTransform()->scale += Vector2D(deltaScale, deltaScale);

		if (trans->scale.x < MIN_SCALE)
			m_isGrowing = true;

		if (trans->scale.x > MAX_SCALE)
			m_isGrowing = false;
	}
}
