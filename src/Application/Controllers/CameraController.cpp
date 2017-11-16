#include "CameraController.h"

#include "../../Base/Math/MathHelper.h"
using namespace Math;

#include "../../Orbis/Game/Transform.h"
#include "../../Orbis/Game/Entity.h"
#include "../../Orbis/Core/TimeManager.h"
using namespace Game;
using namespace Core;

namespace Controllers
{
	void CameraController::Update()
	{
		static const float omega = MathHelper::GetPi() / 8.0f;

		Transform* transform = GetParent()->GetTransform();
		float alpha = transform->GetRotation();
		transform->SetRotation(alpha + TimeManager::GetInstance()->GetDeltaSeconds() * omega);
	}
}
