#include "TestRenderer.h"

#include "..\Video\VideoManager.h"
using namespace Video;

namespace Components
{
	void TestRenderer::Update() { }

	void TestRenderer::Render()
	{
		static const float extent = 0.1f;

		RenderDevice* renderDevice = VideoManager::GetInstance()->GetRenderDevice();
		Entity *entity = GetParentEntity();
		Vector2D position = entity->GetTransformation()->GetPosition();
		
		renderDevice->BeginPrimitive();
		renderDevice->SetVertex2D(Vector2D(position.GetX() - extent, position.GetY() - extent));
		renderDevice->SetVertex2D(Vector2D(position.GetX() + extent, position.GetY() - extent));
		renderDevice->SetVertex2D(Vector2D(position.GetX() + extent, position.GetY() + extent));
		renderDevice->SetVertex2D(Vector2D(position.GetX() - extent, position.GetY() + extent));
		renderDevice->EndPrimitive();
	}
}