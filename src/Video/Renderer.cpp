#include "Renderer.h"

namespace Video
{
	void Renderer::Update() { }

	void Renderer::Render()
	{
		RenderDevice renderDevice = VideoManager::GetInstance().GetRenderDevice();
		Entity *entity = GetEntity();
		Vector2D position = entity->GetTransformation().GetPosition();
		
		renderDevice.BeginPrimitive();
		renderDevice.SetVertex2D(Vector2D(position.GetX() - 0.5f, position.GetY() - 0.5f));
		renderDevice.SetVertex2D(Vector2D(position.GetX() + 0.5f, position.GetY() - 0.5f));
		renderDevice.SetVertex2D(Vector2D(position.GetX() + 0.5f, position.GetY() + 0.5f));
		renderDevice.SetVertex2D(Vector2D(position.GetX() - 0.5f, position.GetY() + 0.5f));
		renderDevice.EndPrimitive();
	}
}