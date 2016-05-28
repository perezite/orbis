#include "Camera.h"

#include "..\Video\VideoManager.h"
using namespace Video;

namespace Components
{
	void Components::Camera::Update()
	{
		RenderDevice* renderDevice = VideoManager::GetInstance()->GetRenderDevice();
		Transform* transform = GetParent()->GetTransform();
		Vector2D inverseScale = Vector2D(1.0f / transform->GetScale().GetX(), 1.0f / transform->GetScale().GetY());

		renderDevice->ResetGlobalTransforms();
		renderDevice->ApplyGlobalRotation(-transform->GetRotation());
		renderDevice->ApplyGlobalScale(inverseScale);
		renderDevice->ApplyGlobalTranslation(-transform->GetPosition());
	}
}
