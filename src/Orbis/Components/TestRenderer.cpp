#include "TestRenderer.h"

#include "..\Video\VideoManager.h"
using namespace Video;

#include "..\Game\Entity.h"
using namespace Game;

namespace Components
{
	void TestRenderer::Update() { }

	void TestRenderer::Render()
	{
		static const float extent = 0.1f;

		RenderDevice* renderDevice = VideoManager::GetInstance()->GetRenderDevice();
		Entity *entity = GetParent();
		Vector2D position = entity->GetTransform()->GetPosition();
		
		renderDevice->BeginPrimitive();
		renderDevice->SetVertex2D(Vector2D(position.GetX() - extent, position.GetY() - extent));
		renderDevice->SetVertex2D(Vector2D(position.GetX() + extent, position.GetY() - extent));
		renderDevice->SetVertex2D(Vector2D(position.GetX() + extent, position.GetY() + extent));
		renderDevice->SetVertex2D(Vector2D(position.GetX() - extent, position.GetY() + extent));
		renderDevice->EndPrimitive();
	}
}