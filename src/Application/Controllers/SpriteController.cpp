#include "SpriteController.h"

#include "../../Base/Math/MathHelper.h"
#include "../../Orbis/Game/Transform.h"
#include "../../Orbis/Game/Entity.h"
#include "../../Orbis/Core/TimeManager.h"
using namespace Math;
using namespace Game;
using namespace Core;

namespace Controllers
{
	void SpriteController::Update()
	{
		static const float omega = MathHelper::GetPi();

		Transform* transform = GetParent()->GetTransform();
		float alpha = transform->GetRotation();
		transform->SetRotation(alpha + TimeManager::GetInstance()->GetDeltaSeconds() * omega);
	}
}
